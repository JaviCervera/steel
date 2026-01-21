extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "interface/file_system.h"
#include "procedural/engine_internal.h"
#include "procedural/memblock.h"
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

    // Move definitions into global namespace
    luaL_dostring(m_state, "for k,v in pairs(steel) do _G[k]=v end");
  }

  ~ScriptingLua()
  {
    lua_close(m_state);
  }

  bool load(const char *filename)
  {
    Memblock *memblock = LoadMemblock(filename);
    if (!memblock)
    {
      m_error = std::string("Cannot load script file '") + filename + "'";
      return false;
    }
    if (luaL_loadbuffer(m_state, (const char *)memblock, GetMemblockSize(memblock), filename) || lua_pcall(m_state, 0, LUA_MULTRET, 0))
    {
      m_error = lua_tostring(m_state, -1);
      FreeMemblock(memblock);
      return false;
    }
    FreeMemblock(memblock);
    return true;
  }

  const char *error() const
  {
    return m_error.c_str();
  }

private:
  lua_State *m_state;
  std::string m_error;
};
