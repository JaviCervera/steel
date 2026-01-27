#include "../interface/audio_manager.h"
#include "engine_internal.h"
#include "listener.h"

extern "C"
{
	EXPORT void CALL SetListener(float x, float y, float z, float yaw)
	{
		GetEngine().audioManager().listener(x, y, z, yaw);
	}
}
