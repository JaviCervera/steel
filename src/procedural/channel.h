/**
 * @file
 * A channel is a playback handle for sound effects. Multiple channels can play simultaneously,
 * allowing for concurrent audio playback with independent control over each stream.
 */
#pragma once

#include "common.h"

typedef int Channel;
struct Sound;

extern "C"
{
	/**
	 * Stops playback on a channel immediately.
	 *
	 * @param channel The channel to stop.
	 */
	EXPORT void CALL StopChannel(Channel channel);

	/**
	 * Pauses playback on a channel.
	 *
	 * @param channel The channel to pause.
	 */
	EXPORT void CALL PauseChannel(Channel channel);

	/**
	 * Resumes playback on a paused channel.
	 *
	 * @param channel The channel to resume.
	 */
	EXPORT void CALL ResumeChannel(Channel channel);

	/**
	 * Sets the 3D position of the sound playing on a channel.
	 *
	 * @param channel The channel.
	 * @param x The x-coordinate in world space.
	 * @param y The y-coordinate in world space.
	 * @param z The z-coordinate in world space.
	 */
	EXPORT void CALL SetChannel3DPosition(Channel channel, float x, float y, float z);

	/**
	 * Sets the distance attenuation parameters for a 3D sound channel.
	 *
	 * @param channel The channel.
	 * @param min_dist The minimum distance for attenuation.
	 * @param max_dist The maximum distance for attenuation.
	 * @param rolloff The rolloff factor controlling attenuation rate.
	 */
	EXPORT void CALL SetChannelAttenuation(Channel channel, float min_dist, float max_dist, float rolloff);

	/**
	 * Sets the pitch (playback speed) of a channel.
	 *
	 * @param channel The channel.
	 * @param pitch The pitch multiplier (1.0 = normal speed).
	 */
	EXPORT void CALL SetChannelPitch(Channel channel, float pitch);

	/**
	 * Sets the volume of a channel.
	 *
	 * @param channel The channel.
	 * @param volume The volume level (0.0 to 1.0).
	 */
	EXPORT void CALL SetChannelVolume(Channel channel, float volume);

	/**
	 * Sets the stereo pan of a channel.
	 *
	 * @param channel The channel.
	 * @param pan The pan value (-1.0 = left, 0.0 = center, 1.0 = right).
	 */
	EXPORT void CALL SetChannelPan(Channel channel, float pan);

	/**
	 * Checks if a channel is currently playing.
	 *
	 * @param channel The channel to check.
	 * @return True if the channel is playing, false otherwise.
	 */
	EXPORT bool_t CALL IsChannelPlaying(Channel channel);
}
