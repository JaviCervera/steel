/**
 * @file
 * Screen management and window control.
 * Handles window creation, resizing, refresh rate, and timing information.
 */
#pragma once

#include "common.h"

extern "C"
{
	/**
	 * Opens a game window with specified dimensions and fullscreen setting.
	 *
	 * @param width The window width in pixels.
	 * @param height The window height in pixels.
	 * @param fullscreen True for fullscreen mode, false for windowed.
	 */
	EXPORT void CALL OpenScreen(int width, int height, bool_t fullscreen);

	/**
	 * Closes the game window.
	 */
	EXPORT void CALL CloseScreen();

	/**
	 * Sets the title text for the game window.
	 *
	 * @param title The title string.
	 */
	EXPORT void CALL SetScreenTitle(const char *title);

	/**
	 * Allows the user to resize the game window.
	 *
	 * @param resizable True to allow resizing, false to disable.
	 */
	EXPORT void CALL SetScreenResizable(bool_t resizable);

	/**
	 * Sets the target frame rate for the game.
	 *
	 * @param fps The target frames per second.
	 */
	EXPORT void CALL SetScreenFPS(int fps);

	/**
	 * Refreshes the screen and flips the back buffer (displays rendered frame).
	 * This should be called once per frame.
	 */
	EXPORT void CALL RefreshScreen();

	/**
	 * Checks if the screen window is currently open.
	 *
	 * @return True if the screen is open, false otherwise.
	 */
	EXPORT bool_t CALL IsScreenOpened();

	/**
	 * Gets the current width of the screen in pixels.
	 *
	 * @return The screen width.
	 */
	EXPORT int CALL GetScreenWidth();

	/**
	 * Gets the current height of the screen in pixels.
	 *
	 * @return The screen height.
	 */
	EXPORT int CALL GetScreenHeight();

	/**
	 * Gets the current frame rate in frames per second.
	 *
	 * @return The current FPS.
	 */
	EXPORT int CALL GetScreenFPS();

	/**
	 * Gets the desktop width in pixels.
	 *
	 * @return The desktop width.
	 */
	EXPORT int CALL GetDesktopWidth();

	/**
	 * Gets the desktop height in pixels.
	 *
	 * @return The desktop height.
	 */
	EXPORT int CALL GetDesktopHeight();

	/**
	 * Gets the elapsed time since the last frame in seconds.
	 *
	 * @return The delta time.
	 */
	EXPORT float CALL GetDelta();
}
