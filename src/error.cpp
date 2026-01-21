#include <stdio.h>
#include <stdlib.h>
#include "error.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

void Error(const char *msg)
{
#ifdef _WIN32
  MessageBoxA(NULL, msg, "Error", MB_OK | MB_ICONERROR);
#else
  fprintf(stderr, "Error: %s\n", msg);
#endif
  exit(EXIT_FAILURE);
}
