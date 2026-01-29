#include <irrlicht.h>
#include <soloud.h>
#include <soloud_wav.h>
#include <soloud_wavstream.h>
#include "../interface/audio_manager.h"
#include "../interface/file_system.h"

#define MIN_DISTANCE 0.0001f

struct Position
{
	float pos[3];
	float vel[3];

	Position(float x = 0, float y = 0, float z = 0)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
		vel[0] = 0;
		vel[1] = 0;
		vel[2] = 0;
	}

	Position &operator=(const Position &other)
	{
		vel[0] += other.pos[0] - pos[0];
		vel[1] += other.pos[1] - pos[1];
		vel[2] += other.pos[2] - pos[2];
		pos[0] = other.pos[0];
		pos[1] = other.pos[1];
		pos[2] = other.pos[2];
		return *this;
	}
};

struct AudioManagerSoLoud : public AudioManager
{
	AudioManagerSoLoud(FileSystem &fs)
			: m_fs(&fs),
				m_soloud(),
				m_music(NULL),
				m_music_handle(0),
				m_listener(),
				m_positions()
	{
		m_soloud.init(SoLoud::Soloud::LEFT_HANDED_3D);
	}

	~AudioManagerSoLoud()
	{
		m_soloud.deinit();
	}

	void stopChannel(Channel channel)
	{
		m_soloud.stop(channel);
	}

	void pauseChannel(Channel channel)
	{
		m_soloud.setPause(channel, true);
	}

	void resumeChannel(Channel channel)
	{
		m_soloud.setPause(channel, false);
	}

	void channel3DPosition(Channel channel, float x, float y, float z)
	{
		m_positions[channel] = Position(x, y, z);
		const Position &pos = m_positions[channel];
		m_soloud.set3dSourcePosition(channel, x, y, z);
		m_soloud.set3dSourceVelocity(channel, pos.vel[0], pos.vel[1], pos.vel[2]);
	}

	void channelRadius(Channel channel, float radius)
	{
		m_soloud.set3dSourceMinMaxDistance(channel, MIN_DISTANCE, radius);
	}

	void channelPitch(Channel channel, float pitch)
	{
		m_soloud.setRelativePlaySpeed(channel, pitch);
	}

	void channelVolume(Channel channel, float volume)
	{
		m_soloud.setVolume(channel, volume);
	}

	void channelPan(Channel channel, float pan)
	{
		m_soloud.setPan(channel, pan);
	}

	bool isChannelPlaying(Channel channel)
	{
		return m_soloud.isValidVoiceHandle(channel);
	}

	void listener(float x, float y, float z, float yaw)
	{
		const float atX = sin(yaw) * irr::core::RADTODEG;
		const float atY = 0;
		const float atZ = cos(yaw) * irr::core::RADTODEG;
		m_listener = Position(x, y, z);
		m_soloud.set3dListenerParameters(x, y, z, atX, atY, atZ, 0, 1, 0, m_listener.vel[0], m_listener.vel[1], m_listener.vel[2]);
	}

	bool playMusic(const char *filename, bool loop)
	{
		const size_t size = m_fs->fileSize(filename);
		if (size == size_t(-1))
			return false;
		unsigned char *data = new unsigned char[size];
		m_fs->readFile(filename, data, size);
		SoLoud::WavStream *new_music = new SoLoud::WavStream();
		SoLoud::handle new_handle = 0;
		SoLoud::result result = new_music->loadMem(data, size, true, true);
		delete[] data;
		if (result == SoLoud::SO_NO_ERROR)
		{
			new_music->setLooping(true);
			new_handle = m_soloud.play(*new_music);
		}
		else
		{
			delete new_music;
		}
		if (new_handle)
		{
			stopMusic();
			m_music = new_music;
			m_music_handle = new_handle;
		}
		return result == SoLoud::SO_NO_ERROR && new_handle != 0;
	}

	void stopMusic()
	{
		if (isMusicPlaying())
			m_soloud.stop(m_music_handle);
		if (m_music)
			delete m_music;
		m_music = NULL;
		m_music_handle = 0;
	}

	void pauseMusic()
	{
		m_soloud.setPause(m_music_handle, true);
	}

	void resumeMusic()
	{
		m_soloud.setPause(m_music_handle, false);
	}

	void musicVolume(float volume)
	{
		m_soloud.setVolume(m_music_handle, volume);
	}

	bool isMusicPlaying()
	{
		return m_soloud.isValidVoiceHandle(m_music_handle);
	}

	Sound *loadSound(const char *filename)
	{
		const size_t size = m_fs->fileSize(filename);
		if (size == size_t(-1))
			return NULL;
		unsigned char *data = new unsigned char[size];
		m_fs->readFile(filename, data, size);
		SoLoud::Wav *sound = new SoLoud::Wav();
		SoLoud::result result = sound->loadMem(data, size, true, true);
		delete[] data;
		if (result != SoLoud::SO_NO_ERROR)
		{
			delete sound;
			sound = NULL;
		}
		return (Sound *)sound;
	}

	void freeSound(Sound *sound)
	{
		if (sound)
		{
			m_soloud.stopAudioSource(*(SoLoud::AudioSource *)sound);
			delete (SoLoud::Wav *)sound;
		}
	}

	Channel playSound(Sound *sound, bool loop)
	{
		((SoLoud::AudioSource *)sound)->setLooping(loop);
		SoLoud::handle channel = m_soloud.play(*(SoLoud::AudioSource *)sound);
		m_positions.remove(channel);
		return channel;
	}

	Channel playSound3D(Sound *sound, float x, float y, float z, float radius, bool loop)
	{
		((SoLoud::AudioSource *)sound)->setLooping(loop);
		SoLoud::handle channel = m_soloud.play3d(*(SoLoud::AudioSource *)sound, x, y, z);
		m_positions.remove(channel);
		m_positions[channel] = Position(x, y, z);
		m_soloud.set3dSourceMinMaxDistance(channel, MIN_DISTANCE, radius);
		return channel;
	}

	void update()
	{
		m_soloud.update3dAudio();
		m_listener.vel[0] = 0;
		m_listener.vel[1] = 0;
		m_listener.vel[2] = 0;
		for (PositionMap::Iterator it = m_positions.getIterator(); !it.atEnd(); it++)
		{
			it->getValue() = Position();
		}
	}

private:
	typedef irr::core::map<SoLoud::handle, Position> PositionMap;

	FileSystem *m_fs;
	SoLoud::Soloud m_soloud;
	SoLoud::WavStream *m_music;
	SoLoud::handle m_music_handle;
	Position m_listener;
	PositionMap m_positions; // Channel positions
};
