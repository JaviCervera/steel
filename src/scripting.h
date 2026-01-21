#pragma once

struct Scripting
{
  virtual bool loadScript(const char *filename) = 0;
  virtual const char *error() const = 0;
};
