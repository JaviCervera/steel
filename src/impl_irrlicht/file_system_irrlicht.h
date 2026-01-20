#pragma once

#include <irrlicht.h>
#include "../interface/file_system.h"
#include "platform_irrlicht.h"

struct FileSystemIrrlicht : public FileSystem
{
  FileSystemIrrlicht(PlatformIrrlicht &platform) : m_platform(&platform) {}

  bool addZip(const char *filename)
  {
    if (fs().existFile(filename))
    {
      return fs().addZipFileArchive(filename, true, false);
    }
    return false;
  }

  std::vector<std::string> dirContents(const char *dir) const
  {
    std::vector<std::string> contents;
    const std::string current = fs().getWorkingDirectory();
    fs().changeWorkingDirectoryTo(dir);
    irr::io::IFileList *list = fs().createFileList();
    for (irr::u32 i = 0; i < list->getFileCount(); ++i)
      contents.push_back(list->getFileName(i));
    list->drop();
    fs().changeWorkingDirectoryTo(current.c_str());
    return contents;
  }

  void changeDir(const char *dir)
  {
    fs().changeWorkingDirectoryTo(dir);
  }

  const char *currentDir() const
  {
    return fs().getWorkingDirectory();
  }

  size_t fileSize(const char *filename) const
  {
    if (!fs().existFile(filename))
      return size_t(-1);
    irr::io::IReadFile *file = fs().createAndOpenFile(filename);
    const size_t size = size_t(file->getSize());
    file->drop();
    return size;
  }

  size_t readFile(const char *filename, void *buffer, size_t max_size) const
  {
    if (!fs().existFile(filename))
      return 0;
    irr::io::IReadFile *file = fs().createAndOpenFile(filename);
    const size_t read_size = file->read(buffer, max_size);
    file->drop();
    return read_size;
  }

  bool writeFile(const char *filename, void *buffer, size_t size, bool append = false)
  {
    irr::io::IWriteFile *file = fs().createAndWriteFile(filename, append);
    if (!file)
      return false;
    file->write(buffer, size);
    file->drop();
    return true;
  }

private:
  PlatformIrrlicht *m_platform;

  irr::io::IFileSystem &fs() const
  {
    return *m_platform->device().getFileSystem();
  }
};
