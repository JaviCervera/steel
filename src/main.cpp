#include <stdio.h>
#include "procedural/color.h"
#include "procedural/drawing.h"
#include "procedural/engine.h"
#include "procedural/screen.h"

int main()
{
  InitEngine();
  OpenScreen(800, 600, FALSE);
  while (IsScreenOpened())
  {
    Cls(RGB(0, 0, 64));
    SetColor(RGB(255, 128, 0));
    DrawRect(300, 300, 100, 100);
    RefreshScreen();
  }
  FinishEngine();
  return 0;
}
