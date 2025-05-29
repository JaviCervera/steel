#pragma once

#include "../include/engine.h"
#include "file_system_irrlicht.h"
#include "graphics_irrlicht.h"
#include "platform_irrlicht.h"
#include "screen_irrlicht.h"

struct EngineIrrlicht : public Engine
{
  EngineIrrlicht()
  : m_platform(),
    m_fs(m_platform),
    m_graphics(m_platform),
    m_screen(m_platform)
  {
  }

  FileSystem &fileSystem()
  {
    return m_fs;
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
  PlatformIrrlicht m_platform;
  FileSystemIrrlicht m_fs;
  GraphicsIrrlicht m_graphics;
  ScreenIrrlicht m_screen;
};
