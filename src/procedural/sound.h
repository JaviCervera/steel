#pragma once

#include "common.h"

typedef int Channel;
struct Sound;

extern "C"
{
	EXPORT Sound *CALL LoadSound(const char *filename);
	EXPORT void CALL FreeSound(Sound *sound);
	EXPORT Channel CALL PlaySound(Sound *sound, bool_t loop);
}
