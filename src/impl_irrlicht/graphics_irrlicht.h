#pragma once

#include <irrlicht.h>
#include "../interface/graphics.h"
#include "platform_irrlicht.h"

struct GraphicsIrrlicht : public Graphics
{
  GraphicsIrrlicht(PlatformIrrlicht &platform)
      : m_platform(&platform),
        m_color(255, 255, 255, 255)
  {
  }

  void cls(int color)
  {
    video().setRenderTarget(NULL, true, false, m_platform->irrColor(color));
  }

  void color(int color)
  {
    m_color = m_platform->irrColor(color);
  }

  void plot(float x, float y)
  {
    line(x, y, x, y);
  }

  void line(float x1, float y1, float x2, float y2)
  {
    video().draw2DLine(irr::core::position2di(x1, y1), irr::core::position2di(x2, y2), m_color);
  }

  void rect(float x, float y, float width, float height)
  {
    video().draw2DRectangle(m_color, irr::core::rect<irr::s32>(x, y, x + width, y + height));
  }

private:
  PlatformIrrlicht *m_platform;
  irr::video::SColor m_color;

  irr::video::IVideoDriver &video()
  {
    return *m_platform->device().getVideoDriver();
  }
};
