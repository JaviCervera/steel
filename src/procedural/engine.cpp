#ifdef _MSC_VER
#include "../impl_irrlicht131/engine_irrlicht.h"
#else
#include "../impl_irrlicht_svn/engine_irrlicht.h"
#endif
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
