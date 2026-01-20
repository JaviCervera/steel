#include "../impl_irrlicht/engine_irrlicht.h"
#include "engine.h"

static EngineIrrlicht *_engine = NULL;

extern "C"
{
  EXPORT void CALL InitEngine()
  {
    if (!_engine)
    {
      _engine = new EngineIrrlicht();
    }
  }

  EXPORT void CALL FinishEngine()
  {
    if (_engine)
    {
      delete _engine;
      _engine = NULL;
    }
  }

  Engine &GetEngine()
  {
    return *_engine;
  }
}
