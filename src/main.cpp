#include <stdio.h>
#include "impl_irrlicht/engine_irrlicht.h"

int main()
{
  Engine_Irrlicht engine;
  engine.screen().open(800, 600, false);
  while (engine.screen().isRunning())
  {
    engine.graphics().cls(Color::multiply(COLOR_BLUE, 0.25f));
    engine.graphics().color(COLOR_ORANGE);
    engine.graphics().rect(300, 300, 100, 100);
    engine.screen().refresh();
  }
  return 0;
}
