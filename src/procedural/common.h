#pragma once

#ifdef _WIN32
#if defined(DLLEXPORT)
#define EXPORT __declspec(dllexport)
#define CALL __stdcall
#elif defined(DLLIMPORT)
#define EXPORT __declspec(dllimport)
#define CALL __stdcall
#else
#define EXPORT
#define CALL
#endif
#else
#define EXPORT
#define CALL
#endif

#ifndef SWIG
typedef int bool_t;
#define FALSE 0
#define TRUE 1
#endif
