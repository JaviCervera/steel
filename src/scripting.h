#pragma once

#include "interface/string.h"

#include "steel_sdk.h"

struct lua_State;

struct Scripting
{
  Scripting();
  ~Scripting();
  bool loadScript(const std::string &filename);
  const std::string &error() const;

private:
  lua_State *m_state;
  SteelSDK m_sdk;
  std::string m_error;

  void initLua();
  void initSdk();
};
