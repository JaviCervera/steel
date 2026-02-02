#include "../interface/audio_manager.h"
#include "engine_internal.h"
#include "sound.h"

extern "C"
{
	EXPORT Sound *CALL LoadSound(const char *filename)
	{
		return GetEngine().audioManager().loadSound(filename);
	}

	EXPORT void CALL FreeSound(Sound *sound)
	{
		GetEngine().audioManager().freeSound(sound);
	}

	EXPORT Channel CALL PlaySound(Sound *sound, bool_t loop)
	{
		return GetEngine().audioManager().playSound(sound, loop);
	}
}
