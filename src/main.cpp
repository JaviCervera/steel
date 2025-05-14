#include <stdio.h>
#include "impl_irrlicht/engine_irrlicht.h"

int main()
{
  Engine_Irrlicht engine;
  engine.platform().openScreen(800, 600, false);
  while (engine.platform().isRunning())
  {
    engine.graphics().cls();
    engine.graphics().rect(300, 300, 100, 100);
    engine.platform().refreshScreen();
  }
  return 0;
}
