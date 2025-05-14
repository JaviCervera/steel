#pragma once

struct Graphics;
struct Platform;

struct Engine
{
  virtual ~Engine() {};
  virtual Graphics &graphics() = 0;
  virtual Platform &platform() = 0;
};
