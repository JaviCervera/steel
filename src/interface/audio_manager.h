#pragma once

typedef int Channel;
struct Sound;

struct AudioManager
{
	virtual ~AudioManager() {}

	virtual void stopChannel(Channel channel) = 0;
	virtual void pauseChannel(Channel channel) = 0;
	virtual void resumeChannel(Channel channel) = 0;
	virtual void channel3DPosition(Channel channel, float x, float y, float z) = 0;
	virtual void channelAttenuation(Channel channel, float min_dist, float max_dist, float rolloff) = 0;
	virtual void channelPitch(Channel channel, float pitch) = 0;
	virtual void channelVolume(Channel channel, float volume) = 0;
	virtual void channelPan(Channel channel, float pan) = 0;
	virtual bool isChannelPlaying(Channel channel) = 0;

	virtual void listener(float x, float y, float z, float yaw) = 0;

	virtual bool playMusic(const char *filename, bool loop) = 0;
	virtual void stopMusic() = 0;
	virtual void pauseMusic() = 0;
	virtual void resumeMusic() = 0;
	virtual void musicVolume(float volume) = 0;
	virtual bool isMusicPlaying() = 0;

	virtual Sound *loadSound(const char *filename) = 0;
	virtual void freeSound(Sound *sound) = 0;
	virtual Channel playSound(Sound *sound, bool loop) = 0;

	virtual void update() = 0;
};
