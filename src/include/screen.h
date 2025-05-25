#pragma once

struct Screen
{
  virtual ~Screen() {}
  virtual void open(int width, int height, bool fullscreen) = 0;
  virtual void close() = 0;
  virtual void title(const char* title) = 0;
  virtual void resizable(bool resizable) = 0;
  virtual void fps(int fps) = 0;
  virtual void refresh() = 0;
  virtual bool isRunning() const = 0;
  virtual int width() const = 0;
  virtual int height() const = 0;
  virtual int fps() const = 0;
  virtual int desktopWidth() const = 0;
  virtual int desktopHeight() const = 0;
  virtual float delta() const = 0;
};
