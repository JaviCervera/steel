#pragma once

#include "interface/string.h"
#include "steel_sdk.h"

struct lua_State;

void SetScriptingDependencies(lua_State &l, SteelSDK &sdk);
std::string LoadString(const std::string &filename);
int LuaImport(lua_State *L);
int LuaLoad(lua_State *L);
void RegisterFunction(const char *name, int (*f)(void *));
int GetBoolArg(void *context, int index);
int GetIntArg(void *context, int index);
float GetFloatArg(void *context, int index);
const char *GetStringArg(void *context, int index);
const void *GetPointerArg(void *context, int index);
void PushBool(void *context, int val);
void PushInt(void *context, int val);
void PushFloat(void *context, float val);
void PushString(void *context, const char *val);
void PushPointer(void *context, void *val);
