/**
 * @file
 * Animated models are a likoe normal models, but can support skeletal animations.
 * They are loaded from files and provide frame-based animation control with support
 * for looping and custom frame ranges.
 * Animated models are entities, so any entity function can be used on them, such as
 * setting their position, rotation, scale, etc.
 */
#pragma once

#include "common.h"

struct AnimModel;

extern "C"
{
	/**
	 * Loads an animated model from a file. Both models will share the same
	 * underlying data to save memory, but will have independent animation states.
	 *
	 * @param path The file path to the animated model.
	 * @return A new animated model, or NULL if loading fails.
	 */
	EXPORT AnimModel *CALL LoadAnimModel(const char *path);

	/**
	 * Creates a copy of an animated model.
	 *
	 * @param model The animated model to copy.
	 * @return A new copy of the animated model.
	 */
	EXPORT AnimModel *CALL CopyAnimModel(const AnimModel *model);

	/**
	 * Enables or disables looping for an animated model.
	 *
	 * @param model The animated model.
	 * @param enabled True to enable looping, false to disable.
	 */
	EXPORT void CALL SetAnimModelLoopEnabled(AnimModel *model, bool_t enabled);

	/**
	 * Sets the playback speed of an animated model in frames per second.
	 *
	 * @param model The animated model.
	 * @param fps The frames per second playback speed.
	 */
	EXPORT void CALL SetAnimModelFps(AnimModel *model, float fps);

	/**
	 * Sets the current animation frame of the model.
	 *
	 * @param model The animated model.
	 * @param frame The frame number to set.
	 */
	EXPORT void CALL SetAnimModelFrame(AnimModel *model, float frame);

	/**
	 * Gets the current animation frame of the model.
	 *
	 * @param model The animated model.
	 * @return The current frame number.
	 */
	EXPORT float CALL GetAnimModelFrame(const AnimModel *model);

	/**
	 * Sets the animation frame range for playback.
	 *
	 * @param model The animated model.
	 * @param first The first frame number.
	 * @param last The last frame number.
	 */
	EXPORT void CALL SetAnimModelFrameRange(AnimModel *model, float first, float last);

	/**
	 * Gets the first frame number of the animation.
	 *
	 * @param model The animated model.
	 * @return The first frame number.
	 */
	EXPORT float CALL GetAnimModelFirstFrame(const AnimModel *model);

	/**
	 * Gets the last frame number of the animation.
	 *
	 * @param model The animated model.
	 * @return The last frame number.
	 */
	EXPORT float CALL GetAnimModelLastFrame(const AnimModel *model);
}
