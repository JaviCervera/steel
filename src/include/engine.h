#pragma once

struct Graphics;
struct Screen;

struct Engine
{
  virtual ~Engine() {};
  virtual Graphics &graphics() = 0;
  virtual Screen &screen() = 0;
};
