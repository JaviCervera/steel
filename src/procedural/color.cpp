#include "../interface/color.h"
#include "color.h"

extern "C"
{
  EXPORT int CALL RGB(int r, int g, int b)
  {
    return Color::rgb(r, g, b);
  }

  EXPORT int CALL RGBA(int r, int g, int b, int a)
  {
    return Color::rgb(r, g, b, a);
  }

  EXPORT int CALL GetRed(int color)
  {
    return Color::red(color);
  }

  EXPORT int CALL GetGreen(int color)
  {
    return Color::green(color);
  }

  EXPORT int CALL GetBlue(int color)
  {
    return Color::blue(color);
  }

  EXPORT int CALL GetAlpha(int color)
  {
    return Color::alpha(color);
  }

  EXPORT int CALL FadeColor(int color, int new_alpha)
  {
    return Color::fade(color, new_alpha);
  }

  EXPORT int CALL MultiplyColor(int color, float factor)
  {
    return Color::multiply(color, factor);
  }

  EXPORT int CALL SwapColor(int color)
  {
    return Color::swap(color);
  }
}
