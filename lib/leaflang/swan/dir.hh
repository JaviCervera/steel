// note: on visual studio, if you include this file dirent.h must be present

#ifndef SWAN_DIR_INCLUDED
#define SWAN_DIR_INCLUDED

#include "string.hh"
#include "vector.hh"
#include <stdio.h>
#include <stdlib.h>

#ifndef _MSC_VER
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#define _getcwd getcwd
#define _chdir chdir
#define _mkdir mkdir
#define _rmdir rmdir
#else
#include <direct.h>
#include "dirent.h"
//#undef CopyFile
//#undef DeleteFile
#endif

#ifdef _WIN32
#define realpath(N,R) _fullpath((R),(N),_MAX_PATH)
#endif

namespace swan
{
  namespace dir
  {
    inline std::vector<std::string> contents(const std::string& path)
    {
      std::vector<std::string> arr;

      // open directory
      DIR* d = (DIR*)opendir(path.c_str());
      if (d == NULL) return arr;

      // copy directory contents
      struct dirent* entry;
      while ((entry = (struct dirent*)readdir(d)))
      {
        arr.push_back(entry->d_name);
      }

      // close directory
      closedir(d);

      return arr;
    }

    inline std::string current()
    {
      char buf[FILENAME_MAX];
      _getcwd(buf, FILENAME_MAX);
      return std::string(buf);
    }

    inline bool change(const std::string& path)
    {
      return _chdir(path.c_str()) == 0;
    }

    inline void create(const std::string& path)
    {
#ifdef _WIN32
      _mkdir(path.c_str());
#else
      _mkdir(path.c_str(), S_IRWXU | S_IRGRP | S_IXGRP);
#endif
    }

    inline void remove(const std::string& path)
    {
      _rmdir(path.c_str());
    }

    inline std::string real_path(const std::string& path)
    {
      char out_path[FILENAME_MAX];
      realpath(path.c_str(), out_path);
      return std::string(out_path);
    }
  } // namespace dir
} // namespace swan

#endif // SWAN_DIR_INCLUDED
