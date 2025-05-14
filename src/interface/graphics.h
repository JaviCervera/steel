#pragma once

struct Graphics
{
  virtual ~Graphics() {};

  virtual void cls() = 0;
  virtual void point(float x, float y) = 0;
  virtual void line(float x1, float y1, float x2, float y2) = 0;
  virtual void rect(float x, float y, float width, float height) = 0;
};
