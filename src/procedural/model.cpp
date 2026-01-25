#include "../interface/model_manager.h"
#include "engine_internal.h"
#include "model.h"

extern "C"
{
	EXPORT Model *CALL CreateCubeModel()
	{
		return GetEngine().modelManager().createCubeModel();
	}

	EXPORT Model *CALL CreateSphereModel()
	{
		return GetEngine().modelManager().createSphereModel();
	}
}
