extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "scripting.h"
#include "scripting_utils.h"

extern "C" int luaopen_steel(lua_State *l);

Scripting::Scripting()
{
  initLua();
  initSdk();
  SetScriptingDependencies(*m_state, m_sdk);
}

Scripting::~Scripting()
{
  lua_close(m_state);
}

bool Scripting::loadScript(const std::string &filename)
{
  const std::string content = LoadString(filename);
  if (content == "")
  {
    m_error = std::string("Cannot load script file '") + filename + "'";
    return false;
  }
  if (luaL_loadbuffer(m_state, content.c_str(), content.size(), filename.c_str()) || lua_pcall(m_state, 0, LUA_MULTRET, 0))
  {
    m_error = lua_tostring(m_state, -1);
    return false;
  }
  return true;
}

const std::string &Scripting::error() const
{
  return m_error;
}

void Scripting::initLua()
{
  // Create Lua state and register libs
  m_state = luaL_newstate();
  luaL_openlibs(m_state);
  luaopen_steel(m_state);
  lua_register(m_state, "import", LuaImport);
  lua_register(m_state, "load", LuaLoad);

  // Move definitions into global namespace
  luaL_dostring(m_state, "for k,v in pairs(steel) do _G[k]=v end");
}

void Scripting::initSdk()
{
  m_sdk.RegisterFunction = RegisterFunction;
  m_sdk.GetBoolArg = GetBoolArg;
  m_sdk.GetIntArg = GetIntArg;
  m_sdk.GetFloatArg = GetFloatArg;
  m_sdk.GetStringArg = GetStringArg;
  m_sdk.GetPointerArg = GetPointerArg;
  m_sdk.PushBool = PushBool;
  m_sdk.PushInt = PushInt;
  m_sdk.PushFloat = PushFloat;
  m_sdk.PushString = PushString;
  m_sdk.PushPointer = PushPointer;
}
