#pragma once

#include <irrlicht.h>
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif
#define STB_VORBIS_HEADER_ONLY
#include "../../lib/stb/stb_vorbis.c"
#undef STB_VORBIS_HEADER_ONLY
#include "../interface/audio_manager.h"
#include "../interface/file_system.h"

#define BUFFER_SIZE 4096 * 8

inline ALenum formatFromInfo(short channels)
{
	if (channels == 1)
		return AL_FORMAT_MONO16;
	return AL_FORMAT_STEREO16;
}

struct AudioStream
{
	ALuint source;
	stb_vorbis *stream;
	stb_vorbis_info info;
	ALuint buffers[2];
	size_t samples_left;
	bool loop;
	unsigned char *data;

	AudioStream(ALuint source, stb_vorbis *stream, bool loop, unsigned char *data)
			: source(source),
				stream(stream),
				info(),
				samples_left(0),
				loop(loop),
				data(data)
	{
		buffers[0] = 0;
		buffers[1] = 0;
	}

	~AudioStream()
	{
		delete[] data;
	}

	bool update(size_t buffer_index)
	{
		ALshort pcm[BUFFER_SIZE];
		const int size = stb_vorbis_get_samples_short_interleaved(stream, info.channels, pcm, BUFFER_SIZE);
		if (size == 0)
			return false;
		alBufferData(
				buffers[buffer_index],
				formatFromInfo(info.channels),
				pcm,
				size * info.channels * sizeof(ALshort), info.sample_rate);
		samples_left -= size;
		return true;
	}
};

struct Sound
{
	ALuint id;
	Sound(ALuint id) : id(id) {}
};

struct AudioManagerOpenAL : public AudioManager
{
	AudioManagerOpenAL(FileSystem &fs)
			: m_fs(&fs),
				m_device(NULL),
				m_context(NULL),
				m_music(NULL)
	{
		m_device = alcOpenDevice(NULL);
		if (m_device)
		{
			m_context = alcCreateContext(m_device, NULL);
			alcMakeContextCurrent(m_context);
			alDistanceModel(AL_EXPONENT_DISTANCE);
		}
	}

	~AudioManagerOpenAL()
	{
		if (m_context)
		{
			alcMakeContextCurrent(NULL);
			alcDestroyContext(m_context);
		}
		if (m_device)
		{
			alcCloseDevice(m_device);
		}
	}

	void stopChannel(Channel channel)
	{
		if (channel > 0)
		{
			alSourceStop(static_cast<ALuint>(channel));
			alDeleteSources(1, reinterpret_cast<ALuint *>(&channel));
		}
	}

	void pauseChannel(Channel channel)
	{
		if (channel > 0)
		{
			alSourcePause(static_cast<ALuint>(channel));
		}
	}

	void resumeChannel(Channel channel)
	{
		if (channel > 0)
		{
			alSourcePlay(static_cast<ALuint>(channel));
		}
	}

	void channel3DPosition(Channel channel, float x, float y, float z)
	{
		if (channel > 0)
		{
			const irr::core::vector3df pos(x, y, z);
			irr::core::vector3df vel(0, 0, 0);
			if (m_positions.find(static_cast<ALuint>(channel)))
				vel = pos - m_positions[static_cast<ALuint>(channel)];
			m_positions[static_cast<ALuint>(channel)] = pos;
			alSourcei(static_cast<ALuint>(channel), AL_SOURCE_RELATIVE, AL_FALSE);
			alSource3f(static_cast<ALuint>(channel), AL_POSITION, x, y, -z);
			alSource3f(static_cast<ALuint>(channel), AL_VELOCITY, vel.X, vel.Y, -vel.Z);
		}
	}

	void channelAttenuation(Channel channel, float min_dist, float max_dist, float rolloff)
	{
		if (channel > 0)
		{
			alSourcef(static_cast<ALuint>(channel), AL_REFERENCE_DISTANCE, min_dist);
			alSourcef(static_cast<ALuint>(channel), AL_MAX_DISTANCE, max_dist);
			alSourcef(static_cast<ALuint>(channel), AL_ROLLOFF_FACTOR, rolloff);
		}
	}

	void channelPitch(Channel channel, float pitch)
	{
		if (channel > 0)
		{
			alSourcef(static_cast<ALuint>(channel), AL_PITCH, pitch);
		}
	}

	void channelVolume(Channel channel, float volume)
	{
		if (channel > 0)
		{
			alSourcef(static_cast<ALuint>(channel), AL_GAIN, volume);
		}
	}

	void channelPan(Channel channel, float pan)
	{
		if (channel > 0)
		{
			alSource3f(static_cast<ALuint>(channel), AL_POSITION, pan, 0.0f, 0.0f);
		}
	}

	bool isChannelPlaying(Channel channel)
	{
		if (channel > 0)
		{
			ALint state;
			alGetSourcei(static_cast<ALuint>(channel), AL_SOURCE_STATE, &state);
			return state == AL_PLAYING;
		}
		return false;
	}

	void listener(float x, float y, float z, float yaw)
	{
		const float at_x = sin(yaw * irr::core::DEGTORAD);
		const float at_y = 0;
		const float at_z = cos(yaw * irr::core::DEGTORAD);
		const irr::core::vector3df pos(x, y, z);
		irr::core::vector3df vel = pos - m_listener;
		m_listener = pos;
		float orientation[] = {at_x, at_y, -at_z, 0.0f, 1.0f, 0.0f};
		alListener3f(AL_POSITION, x, y, -z);
		alListener3f(AL_VELOCITY, vel.X, vel.Y, -vel.Z);
		alListenerfv(AL_ORIENTATION, orientation);
	}

	bool playMusic(const char *filename, bool loop)
	{
		stopMusic();

		const size_t size = m_fs->fileSize(filename);
		if (size == size_t(-1))
			return false;

		unsigned char *data = new unsigned char[size];
		m_fs->readFile(filename, data, size);
		stb_vorbis *ogg_stream = stb_vorbis_open_memory(data, static_cast<int>(size), NULL, NULL);
		if (!ogg_stream)
		{
			delete[] data;
			return false;
		}

		ALuint source;
		alGenSources(1, &source);

		m_music = new AudioStream(source, ogg_stream, loop, data);
		m_music->info = stb_vorbis_get_info(ogg_stream);
		m_music->samples_left = stb_vorbis_stream_length_in_samples(ogg_stream) * m_music->info.channels;

		alGenBuffers(2, m_music->buffers);
		if (!m_music->update(0))
		{
			stopMusic();
			return false;
		}
		if (!m_music->update(1))
		{
			stopMusic();
			return false;
		}
		alSourceQueueBuffers(m_music->source, 2, m_music->buffers);
		alSourcePlay(m_music->source);

		return true;
	}

	void stopMusic()
	{
		if (m_music)
		{
			alSourceStop(m_music->source);
			alDeleteSources(1, &m_music->source);
			alDeleteBuffers(2, m_music->buffers);
			stb_vorbis_close(m_music->stream);
			delete m_music;
		}
		m_music = NULL;
	}

	void pauseMusic()
	{
		if (m_music)
		{
			alSourcePause(m_music->source);
		}
	}

	void resumeMusic()
	{
		if (m_music)
		{
			alSourcePlay(m_music->source);
		}
	}

	void musicVolume(float volume)
	{
		if (m_music)
		{
			alSourcef(m_music->source, AL_GAIN, volume);
		}
	}

	bool isMusicPlaying()
	{
		if (m_music)
		{
			ALint state;
			alGetSourcei(m_music->source, AL_SOURCE_STATE, &state);
			return state == AL_PLAYING;
		}
		return false;
	}

	Sound *loadSound(const char *filename)
	{
		const size_t size = m_fs->fileSize(filename);
		if (size == size_t(-1))
			return NULL;
		unsigned char *data = new unsigned char[size];
		m_fs->readFile(filename, data, size);
		stb_vorbis *file = stb_vorbis_open_memory(data, static_cast<int>(size), NULL, NULL);
		if (!file)
		{
			delete[] data;
			return NULL;
		}

		const stb_vorbis_info fileinfo = stb_vorbis_get_info(file);
		const int length_samples = stb_vorbis_stream_length_in_samples(file) * fileinfo.channels;
		short *buffer = new short[length_samples];
		stb_vorbis_get_samples_short_interleaved(file, fileinfo.channels, buffer, length_samples);

		ALuint al_buffer;
		alGenBuffers(1, &al_buffer);
		alBufferData(al_buffer, formatFromInfo(fileinfo.channels), buffer, length_samples * sizeof(short), fileinfo.sample_rate);
		stb_vorbis_close(file);
		delete[] buffer;
		delete[] data;

		return new Sound(al_buffer);
	}

	void freeSound(Sound *sound)
	{
		if (sound)
		{
			alDeleteBuffers(1, &sound->id);
			delete sound;
		}
	}

	Channel playSound(Sound *sound, bool loop)
	{
		ALuint channel;
		alGenSources(1, &channel);
		alSourcei(channel, AL_SOURCE_RELATIVE, AL_TRUE);
		alSourcei(channel, AL_BUFFER, sound->id);
		alSourcei(channel, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
		channelPitch(channel, 1);
		alSourcePlay(channel);
		return channel;
	}

	void update()
	{
		if (m_music)
		{
			ALint processed = 0;
			alGetSourcei(m_music->source, AL_BUFFERS_PROCESSED, &processed);
			while (processed--)
			{
				ALuint buffer;
				alSourceUnqueueBuffers(m_music->source, 1, &buffer);
				bool streamOk = m_music->update(buffer);
				if (streamOk)
				{
					alSourceQueueBuffers(m_music->source, 1, &buffer);
				}
				else if (m_music->loop)
				{
					stb_vorbis_seek_start(m_music->stream);
					m_music->samples_left = stb_vorbis_stream_length_in_samples(m_music->stream) * m_music->info.channels;
					if (m_music->update(buffer))
						alSourceQueueBuffers(m_music->source, 1, &buffer);
				}
			}
		}
	}

private:
	typedef irr::core::map<ALuint, irr::core::vector3df> PositionMap;

	FileSystem *m_fs;
	ALCdevice *m_device;
	ALCcontext *m_context;
	irr::core::vector3df m_listener;
	PositionMap m_positions;
	AudioStream *m_music;
};
