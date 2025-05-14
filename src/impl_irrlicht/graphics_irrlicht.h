#pragma once

#include <irrlicht.h>
#include "../interface/graphics.h"
#include "platform_irrlicht.h"

struct Graphics_Irrlicht : public Graphics
{
  Graphics_Irrlicht(Platform_Irrlicht &platform) : m_platform(&platform) {}

  void cls()
  {
    video().setRenderTarget(NULL, true, false, irr::video::SColor(255, 0, 0, 0));
  }

  void point(float x, float y)
  {
    line(x, y, x, y);
  }

  void line(float x1, float y1, float x2, float y2)
  {
    video().draw2DLine(irr::core::position2di(x1, y1), irr::core::position2di(x2, y2), irr::video::SColor(255, 255, 255, 255));
  }

  void rect(float x, float y, float width, float height)
  {
    video().draw2DRectangle(irr::video::SColor(255, 255, 255, 255), irr::core::rect<irr::s32>(x, y, x + width, y + height));
  }

private:
  Platform_Irrlicht *m_platform;

  irr::video::IVideoDriver &video()
  {
    return *m_platform->device().getVideoDriver();
  }
};
