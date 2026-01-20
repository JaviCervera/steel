#include "../interface/graphics.h"
#include "engine_internal.h"
#include "drawing.h"

extern "C"
{
  EXPORT void CALL Cls(int color)
  {
    GetEngine().graphics().cls(color);
  }

  EXPORT void CALL SetColor(int color)
  {
    GetEngine().graphics().color(color);
  }

  EXPORT void CALL DrawPlot(float x, float y)
  {
    GetEngine().graphics().plot(x, y);
  }

  EXPORT void CALL DrawLine(float x1, float y1, float x2, float y2)
  {
    GetEngine().graphics().line(x1, y1, x2, y2);
  }

  EXPORT void CALL DrawRect(float x, float y, float width, float height)
  {
    GetEngine().graphics().rect(x, y, width, height);
  }
}
