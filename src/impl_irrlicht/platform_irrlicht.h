#pragma once

#include <irrlicht.h>
#define Win32_LEAN_AND_MEAN
#include <Windows.h>
#include "../include/color.h"

struct PlatformIrrlicht
{
  PlatformIrrlicht()
      : m_device(NULL),
        m_running(false),
        m_last_msecs(0),
        m_frame_msecs(0),
        m_delta(0) {}

  ~PlatformIrrlicht()
  {
    closeScreen();
  }

  void openScreen(int width, int height, bool fullscreen)
  {
    closeScreen();
    m_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::s32>(width, height), 32, fullscreen, false, false, NULL);
    if (m_device)
    {
      m_device->getVideoDriver()->beginScene(false, false, irr::video::SColor());
      m_running = true;
      m_last_msecs = m_device->getTimer()->getRealTime();
      m_delta = 0;
    }
  }

  void closeScreen()
  {
    if (m_device)
    {
      m_device->getVideoDriver()->endScene();
      m_device->closeDevice();
      m_device->drop();
      m_device = NULL;
      m_running = false;
    }
  }

  void screenTitle(const char *title)
  {
    if (m_device)
      m_device->setWindowCaption(irr::core::stringw(title).c_str());
  }

  void screenResizable(bool resizable)
  {
    if (m_device)
      m_device->setResizeAble(resizable);
  }

  void screenFPS(int fps)
  {
    if (m_device)
      m_frame_msecs = (fps > 0) ? (1000 / fps) : 0;
  }

  void refreshScreen()
  {
    if (m_device)
    {
      m_device->getVideoDriver()->endScene();
      m_running = m_device->run() && m_device->getVideoDriver() != NULL;
      const int msecs = m_device->getTimer()->getRealTime();
      const int delta_msecs = msecs - m_last_msecs;
      const int wait = m_frame_msecs - delta_msecs;
      const int fixed_wait = (wait > 0) ? wait : 0;
      if (m_running && fixed_wait > 0)
        Sleep(msecs);
      const int msecs_after = m_device->getTimer()->getRealTime();
      m_delta = (msecs_after - m_last_msecs) / 1000.0f;
      m_last_msecs = msecs_after;
      m_device->getVideoDriver()->beginScene(false, false, irr::video::SColor());
    }
  }

  bool isRunning() const
  {
    return m_running;
  }

  int screenWidth() const
  {
    if (m_device)
      return m_device->getVideoDriver()->getScreenSize().Width;
    return 0;
  }

  int screenHeight() const
  {
    if (m_device)
      return m_device->getVideoDriver()->getScreenSize().Height;
    return 0;
  }

  int screenFPS() const
  {
    if (m_device)
      return m_device->getVideoDriver()->getFPS();
    return 0;
  }

  int desktopWidth() const
  {
    if (m_device)
      return m_device->getVideoModeList()->getDesktopResolution().Width;
    return 0;
  }

  int desktopHeight() const
  {
    if (m_device)
      return m_device->getVideoModeList()->getDesktopResolution().Height;
    return 0;
  }

  float delta() const
  {
    return m_delta;
  }

  irr::IrrlichtDevice &device()
  {
    if (!m_device)
      openScreen(640, 480, false);
    return *m_device;
  }

  static irr::video::SColor irrColor(int color)
  {
    return irr::video::SColor(
        Color::alpha(color),
        Color::red(color),
        Color::green(color),
        Color::blue(color));
  }

  static int color(const irr::video::SColor &color)
  {
    return Color::rgb(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
  }

private:
  irr::IrrlichtDevice *m_device;
  bool m_running;
  int m_last_msecs;
  int m_frame_msecs;
  float m_delta;
};
