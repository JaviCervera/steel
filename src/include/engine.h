#pragma once

struct FileSystem;
struct Graphics;
struct Screen;

struct Engine
{
  virtual ~Engine() {};
  virtual FileSystem &fileSystem() = 0;
  virtual Graphics &graphics() = 0;
  virtual Screen &screen() = 0;
};
