#pragma once

#include "../interface/engine.h"
#include "graphics_irrlicht.h"
#include "platform_irrlicht.h"

struct Engine_Irrlicht : public Engine
{
  Engine_Irrlicht()
  : m_platform(),
    m_graphics(m_platform)
  {
  }

  Graphics &graphics()
  {
    return m_graphics;
  }

  Platform &platform()
  {
    return m_platform;
  }

private:
  Platform_Irrlicht m_platform;
  Graphics_Irrlicht m_graphics;
};
