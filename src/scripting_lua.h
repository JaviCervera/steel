extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "interface/file_system.h"
#include "procedural/engine_internal.h"
#include "scripting.h"
#include "string.h"

extern "C" int luaopen_steel(lua_State *l);

struct ScriptingLua : public Scripting
{
  ScriptingLua()
  {
    // Create Lua state and register libs
    m_state = luaL_newstate();
    luaL_openlibs(m_state);
    luaopen_steel(m_state);
    lua_register(m_state, "import", import);

    // Move definitions into global namespace
    luaL_dostring(m_state, "for k,v in pairs(steel) do _G[k]=v end");
  }

  ~ScriptingLua()
  {
    lua_close(m_state);
  }

  bool loadScript(const char *filename)
  {
    if (!filename)
      return false;
    const std::string content = loadString(filename);
    if (content == "")
    {
      m_error = std::string("Cannot load script file '") + filename + "'";
      return false;
    }
    if (luaL_loadbuffer(m_state, content.c_str(), content.size(), filename) || lua_pcall(m_state, 0, LUA_MULTRET, 0))
    {
      m_error = lua_tostring(m_state, -1);
      return false;
    }
    return true;
  }

  const char *error() const
  {
    return m_error.c_str();
  }

private:
  lua_State *m_state;
  std::string m_error;

  static std::string loadString(const std::string &filename)
  {
    const size_t file_size = GetEngine().fileSystem().fileSize(filename.c_str());
    if (file_size == size_t(-1))
      return "";
    char *buffer = static_cast<char *>(calloc(file_size + 1, sizeof(char)));
    GetEngine().fileSystem().readFile(filename.c_str(), buffer, file_size);
    std::string str = buffer;
    free(buffer);
    return str;
  }

  static int import(lua_State *L)
  {
    if (lua_gettop(L) > 0)
    {
      const std::string filename = lua_tostring(L, 1);
      const std::string fixedFilename = (filename.find(".") == std::string::npos)
                                            ? (const std::string)(filename + std::string(".lua"))
                                            : filename;
      const std::string buffer = loadString(fixedFilename);
      if (buffer == "")
      {
        lua_pushstring(L, (std::string("File '") + fixedFilename + "' does not exist or is empty.").c_str());
        lua_error(L);
        return 0;
      }
      if (luaL_loadbuffer(L, buffer.c_str(), buffer.size(), fixedFilename.c_str()) == 0)
      {
        lua_pcall(L, 0, LUA_MULTRET, 0);
      }
      else
      {
        lua_error(L);
      }
    }
    else
    {
      lua_pushstring(L, "'import' requires filename argument.");
      lua_error(L);
    }
    return 0;
  }
};
