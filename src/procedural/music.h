/**
 * @file
 * Music playback functionality for background music tracks.
 * Only one music track can play at a time.
 */
#pragma once

#include "common.h"

extern "C"
{
	/**
	 * Plays a music track from a file.
	 *
	 * @param filename The path to the music file.
	 * @param loop True to loop the music, false to play once.
	 * @return True if the music started successfully, false otherwise.
	 */
	EXPORT bool_t CALL PlayMusic(const char *filename, bool_t loop);

	/**
	 * Stops the current music playback.
	 */
	EXPORT void CALL StopMusic();

	/**
	 * Pauses the current music playback.
	 */
	EXPORT void CALL PauseMusic();

	/**
	 * Resumes paused music playback.
	 */
	EXPORT void CALL ResumeMusic();

	/**
	 * Sets the volume level of the music.
	 *
	 * @param volume The volume level (0.0 to 1.0).
	 */
	EXPORT void CALL SetMusicVolume(float volume);

	/**
	 * Checks if music is currently playing.
	 *
	 * @return True if music is playing, false otherwise.
	 */
	EXPORT bool_t CALL IsMusicPlaying();
}
