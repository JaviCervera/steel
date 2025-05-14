#pragma once

struct Platform
{
  virtual ~Platform() {}
  virtual void openScreen(int width, int height, bool fullscreen) = 0;
  virtual void closeScreen() = 0;
  virtual void setScreenTitle(const char* title) = 0;
  virtual void setScreenResizable(bool resizable) = 0;
  virtual void setScreenFPS(int fps) = 0;
  virtual void refreshScreen() = 0;
  virtual bool isRunning() const = 0;
  virtual int screenWidth() const = 0;
  virtual int screenHeight() const = 0;
  virtual int screenFPS() const = 0;
  virtual int desktopWidth() const = 0;
  virtual int desktopHeight() const = 0;
  virtual float delta() const = 0;
};
