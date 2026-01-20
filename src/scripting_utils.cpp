extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <stdlib.h>
#include "interface/file_system.h"
#include "procedural/engine_internal.h"
#include "scripting_utils.h"
#include "shared_lib.h"

static lua_State *_lua_state = NULL;
static SteelSDK *_sdk = NULL;

void SetScriptingDependencies(lua_State &l, SteelSDK &sdk)
{
  _lua_state = &l;
  _sdk = &sdk;
}

std::string LoadString(const std::string &filename)
{
  const size_t file_size = GetEngine().fileSystem().fileSize(filename.c_str());
  if (file_size == static_cast<size_t>(-1))
    return "";
  char *buffer = static_cast<char *>(calloc(file_size + 1, sizeof(char)));
  GetEngine().fileSystem().readFile(filename.c_str(), buffer, file_size);
  std::string str = buffer;
  free(buffer);
  return str;
}

int LuaImport(lua_State *L)
{
  if (lua_gettop(L) > 0)
  {
    const std::string filename = lua_tostring(L, 1);
    const std::string fixedFilename = (filename.find(".") == std::string::npos)
                                          ? (const std::string)(filename + std::string(".lua"))
                                          : filename;
    const std::string buffer = LoadString(fixedFilename);
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

int LuaLoad(lua_State *L)
{
#ifndef _EMSCRIPTEN
  if (lua_gettop(L) > 0)
  {
    const std::string libname = lua_tostring(L, 1);
    // TODO: Close libs on script cleanup
    SharedLib *lib = new SharedLib(libname.c_str());
    if (!lib->isOpen())
    {
      lua_pushstring(L, (std::string("Library '") + libname + "' could not be loaded.").c_str());
      lua_error(L);
      return 0;
    }
    int (*loader)(SteelSDK *) = (int (*)(SteelSDK *))lib->funcPtr((libname + "_load").c_str());
    if (!loader)
    {
      lua_pushstring(L, (std::string("Library '") + libname + "' does not contain '" + libname + "_load' function.").c_str());
      lua_error(L);
      return 0;
    }
    if (!loader(_sdk))
    {
      lua_pushstring(L, (std::string("Function '") + libname + "_load' returned 0.").c_str());
      lua_error(L);
      return 0;
    }
  }
  else
  {
    lua_pushstring(L, "'load' requires library argument.");
    lua_error(L);
  }
#else
  lua_pushstring(L, "'load' is not supported on the web.");
  lua_error(L);
#endif
  return 0;
}

void RegisterFunction(const char *name, int (*f)(void *))
{
  lua_register(_lua_state, name, (lua_CFunction)f);
}

int GetBoolArg(void *context, int index)
{
  return lua_toboolean((lua_State *)context, index);
}

int GetIntArg(void *context, int index)
{
  return static_cast<int>(lua_tointeger((lua_State *)context, index));
}

float GetFloatArg(void *context, int index)
{
  return static_cast<float>(lua_tonumber((lua_State *)context, index));
}

const char *GetStringArg(void *context, int index)
{
  return lua_tostring((lua_State *)context, index);
}

const void *GetPointerArg(void *context, int index)
{
  return lua_topointer((lua_State *)context, index);
}

void PushBool(void *context, int val)
{
  lua_pushboolean((lua_State *)context, val);
}

void PushInt(void *context, int val)
{
  lua_pushinteger((lua_State *)context, val);
}

void PushFloat(void *context, float val)
{
  lua_pushnumber((lua_State *)context, val);
}

void PushString(void *context, const char *val)
{
  lua_pushstring((lua_State *)context, val);
}

void PushPointer(void *context, void *val)
{
  lua_pushlightuserdata((lua_State *)context, val);
}
