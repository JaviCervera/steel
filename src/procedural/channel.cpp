#include "../interface/audio_manager.h"
#include "engine_internal.h"
#include "channel.h"

extern "C"
{
	EXPORT void CALL StopChannel(Channel channel)
	{
		GetEngine().audioManager().stopChannel(channel);
	}

	EXPORT void CALL PauseChannel(Channel channel)
	{
		GetEngine().audioManager().pauseChannel(channel);
	}

	EXPORT void CALL ResumeChannel(Channel channel)
	{
		GetEngine().audioManager().resumeChannel(channel);
	}

	EXPORT void CALL SetChannel3DPosition(Channel channel, float x, float y, float z)
	{
		GetEngine().audioManager().channel3DPosition(channel, x, y, z);
	}

	EXPORT void CALL SetChannelRadius(Channel channel, float radius)
	{
		GetEngine().audioManager().channelRadius(channel, radius);
	}

	EXPORT void CALL SetChannelPitch(Channel channel, float pitch)
	{
		GetEngine().audioManager().channelPitch(channel, pitch);
	}

	EXPORT void CALL SetChannelVolume(Channel channel, float volume)
	{
		GetEngine().audioManager().channelVolume(channel, volume);
	}

	EXPORT void CALL SetChannelPan(Channel channel, float pan)
	{
		GetEngine().audioManager().channelPan(channel, pan);
	}

	EXPORT bool_t CALL IsChannelPlaying(Channel channel)
	{
		return GetEngine().audioManager().isChannelPlaying(channel);
	}
}
