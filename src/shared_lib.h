#pragma once

#include "string.h"

#ifndef __stdcall
#define __stdcall
#endif

#ifdef _WIN32
extern "C" void *__stdcall LoadLibraryA(const char *);
extern "C" void *__stdcall GetProcAddress(const void *, const char *);
extern "C" int __stdcall FreeLibrary(void *);
#else
#include <dlfcn.h>
#endif

class SharedLib
{
public:
  SharedLib(const char *filename);
  ~SharedLib();
  bool isOpen() const { return m_handle != 0; }
  void *funcPtr(const char *name) const;

private:
  void *m_handle;
};

inline SharedLib::SharedLib(const char *libname)
{
#if defined(_WIN32)
  m_handle = LoadLibraryA((std::string(libname) + ".dll").c_str());
#elif defined(__APPLE__)
  m_handle = dlopen((std::string("./") + libname + ".dylib").c_str(), RTLD_LAZY);
#elif defined(__linux__) || defined(EMSCRIPTEN)
  m_handle = dlopen((std::string("./") + libname + ".so").c_str(), RTLD_LAZY);
#endif
}

inline SharedLib::~SharedLib()
{
  if (m_handle)
  {
#if defined(_WIN32)
    FreeLibrary(m_handle);
#else
    dlclose(m_handle);
#endif
  }
}

inline void *SharedLib::funcPtr(const char *funcname) const
{
  if (m_handle)
  {
#if defined(_WIN32)
    return GetProcAddress(m_handle, funcname);
#else
    std::string str = funcname;
    size_t atpos = str.find('@');
    if (atpos != std::string::npos)
      str = str.substr(0, atpos);
    if (str[0] == '_')
      str = str.substr(1, std::string::npos);
    return dlsym(m_handle, str.c_str());
#endif
  }
  else
  {
    return 0;
  }
}
