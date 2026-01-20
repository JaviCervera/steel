#pragma once

#include "common.h"

extern "C"
{
  EXPORT int CALL RGB(int r, int g, int b);
  EXPORT int CALL RGBA(int r, int g, int b, int a);
  EXPORT int CALL GetRed(int color);
  EXPORT int CALL GetGreen(int color);
  EXPORT int CALL GetBlue(int color);
  EXPORT int CALL GetAlpha(int color);
  EXPORT int CALL FadeColor(int color, int new_alpha);
  EXPORT int CALL MultiplyColor(int color, float factor);
  EXPORT int CALL SwapColor(int color);
}
