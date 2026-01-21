#pragma once

#include "string.h"

struct lua_State;

struct Scripting
{
  Scripting();
  ~Scripting();
  bool loadScript(const std::string &filename);
  const std::string &error() const;

private:
  lua_State *m_state;
  std::string m_error;

  void initLua();
  static std::string loadString(const std::string &filename);
  static int import(lua_State *L);
};
