#include "../interface/screen.h"
#include "engine_internal.h"
#include "screen.h"

extern "C"
{
  EXPORT void CALL OpenScreen(int width, int height, bool_t fullscreen)
  {
    GetEngine().screen().open(width, height, fullscreen);
  }

  EXPORT void CALL CloseScreen()
  {
    GetEngine().screen().close();
  }

  EXPORT void CALL SetScreenTitle(const char *title)
  {
    GetEngine().screen().title(title);
  }

  EXPORT void CALL SetScreenResizable(bool_t resizable)
  {
    GetEngine().screen().resizable(resizable);
  }

  EXPORT void CALL SetScreenFPS(int fps)
  {
    GetEngine().screen().fps(fps);
  }

  EXPORT void CALL RefreshScreen()
  {
    GetEngine().screen().refresh();
  }

  EXPORT bool_t CALL IsScreenOpened()
  {
    return GetEngine().screen().isRunning();
  }

  EXPORT int CALL GetScreenWidth()
  {
    return GetEngine().screen().width();
  }

  EXPORT int CALL GetScreenHeight()
  {
    return GetEngine().screen().height();
  }

  EXPORT int CALL GetScreenFPS()
  {
    return GetEngine().screen().fps();
  }

  EXPORT int CALL GetDesktopWidth()
  {
    return GetEngine().screen().desktopWidth();
  }

  EXPORT int CALL GetDesktopHeight()
  {
    return GetEngine().screen().desktopHeight();
  }

  EXPORT float CALL GetDelta()
  {
    return GetEngine().screen().delta();
  }
}
