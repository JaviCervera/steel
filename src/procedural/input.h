/**
 * @file
 * Mouse and keyboard input detection for player interaction.
 */
#pragma once

#include "common.h"

extern "C"
{
	/**
	 * Sets the visibility of the mouse cursor.
	 *
	 * @param visible True to show the cursor, false to hide it.
	 */
	EXPORT void CALL SetMouseVisible(bool_t visible);

	/**
	 * Sets the absolute screen position of the mouse cursor.
	 *
	 * @param x The screen x-coordinate.
	 * @param y The screen y-coordinate.
	 */
	EXPORT void CALL SetMousePosition(int x, int y);

	/**
	 * Gets the current mouse x-coordinate on screen.
	 *
	 * @return The screen x-coordinate.
	 */
	EXPORT int CALL GetMouseX();

	/**
	 * Gets the current mouse y-coordinate on screen.
	 *
	 * @return The screen y-coordinate.
	 */
	EXPORT int CALL GetMouseY();

	/**
	 * Gets the mouse scroll wheel position.
	 *
	 * @return The scroll wheel value.
	 */
	EXPORT int CALL GetMouseZ();

	/**
	 * Checks if a mouse button is currently held down.
	 *
	 * @param button The mouse button code.
	 * @return True if the button is held down, false otherwise.
	 */
	EXPORT bool_t CALL IsMouseButtonDown(int button);

	/**
	 * Checks if a mouse button was pressed this frame (single event).
	 *
	 * @param button The mouse button code.
	 * @return True if the button was just pressed, false otherwise.
	 */
	EXPORT bool_t CALL IsMouseButtonHit(int button);

	/**
	 * Checks if a keyboard key is currently held down.
	 *
	 * @param key The key code.
	 * @return True if the key is held down, false otherwise.
	 */
	EXPORT bool_t CALL IsKeyDown(int key);

	/**
	 * Checks if a keyboard key was pressed this frame (single event).
	 *
	 * @param key The key code.
	 * @return True if the key was just pressed, false otherwise.
	 */
	EXPORT bool_t CALL IsKeyHit(int key);
}
