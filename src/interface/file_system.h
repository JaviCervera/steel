#pragma once

#include "string.h"
#include "vector.h"

struct FileSystem
{
  virtual bool addZip(const char *filename) = 0;
  virtual std::vector<std::string> dirContents(const char *dir) const = 0;
  virtual void changeDir(const char *dir) = 0;
  virtual const char *currentDir() const = 0;
  virtual size_t fileSize(const char *filename) const = 0;
  virtual size_t readFile(const char *filename, void *buffer, size_t max_size) const = 0;
  virtual bool writeFile(const char *filename, void *buffer, size_t size, bool append = false) = 0;
};
