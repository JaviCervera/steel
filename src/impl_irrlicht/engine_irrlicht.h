#pragma once

#include "../include/engine.h"
#include "graphics_irrlicht.h"
#include "platform_irrlicht.h"
#include "screen_irrlicht.h"

struct Engine_Irrlicht : public Engine
{
  Engine_Irrlicht()
  : m_platform(),
    m_graphics(m_platform),
    m_screen(m_platform)
  {
  }

  Graphics &graphics()
  {
    return m_graphics;
  }

  Screen &screen()
  {
    return m_screen;
  }

private:
  Platform_Irrlicht m_platform;
  Graphics_Irrlicht m_graphics;
  Screen_Irrlicht m_screen;
};
