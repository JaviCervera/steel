/**
 * @file
 * Sound effect loading and playback.
 * Sound effects can be played on various channels with different parameters.
 */
#pragma once

#include "common.h"

typedef int Channel;
struct Sound;

extern "C"
{
	/**
	 * Loads a sound effect from a file.
	 *
	 * @param filename The path to the sound file.
	 * @return A new sound, or NULL if loading fails.
	 */
	EXPORT Sound *CALL LoadSound(const char *filename);

	/**
	 * Frees a sound and releases its resources.
	 *
	 * @param sound The sound to free.
	 */
	EXPORT void CALL FreeSound(Sound *sound);

	/**
	 * Plays a sound effect.
	 *
	 * @param sound The sound to play.
	 * @param loop True to loop the sound, false to play once.
	 * @return A channel handle for this playback.
	 */
	EXPORT Channel CALL PlaySound(Sound *sound, bool_t loop);
}
