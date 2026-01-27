#include "../interface/audio_manager.h"
#include "engine_internal.h"
#include "music.h"

extern "C"
{
	EXPORT bool_t CALL PlayMusic(const char *filename, bool_t loop)
	{
		return GetEngine().audioManager().playMusic(filename, loop);
	}

	EXPORT void CALL StopMusic()
	{
		GetEngine().audioManager().stopMusic();
	}

	EXPORT void CALL PauseMusic()
	{
		GetEngine().audioManager().pauseMusic();
	}

	EXPORT void CALL ResumeMusic()
	{
		GetEngine().audioManager().resumeMusic();
	}

	EXPORT void CALL SetMusicVolume(float volume)
	{
		GetEngine().audioManager().musicVolume(volume);
	}

	EXPORT bool_t CALL IsMusicPlaying()
	{
		return GetEngine().audioManager().isMusicPlaying();
	}
}
