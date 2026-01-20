#pragma once

#include "common.h"

extern "C"
{
  EXPORT void CALL Cls(int color);
  EXPORT void CALL SetColor(int color);
  EXPORT void CALL DrawPlot(float x, float y);
  EXPORT void CALL DrawLine(float x1, float y1, float x2, float y2);
  EXPORT void CALL DrawRect(float x, float y, float width, float height);
}
