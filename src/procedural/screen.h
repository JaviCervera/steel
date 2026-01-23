#pragma once

#include "common.h"

extern "C"
{
	EXPORT void CALL OpenScreen(int width, int height, bool_t fullscreen);
	EXPORT void CALL CloseScreen();
	EXPORT void CALL SetScreenTitle(const char *title);
	EXPORT void CALL SetScreenResizable(bool_t resizable);
	EXPORT void CALL SetScreenFPS(int fps);
	EXPORT void CALL RefreshScreen();
	EXPORT bool_t CALL IsScreenOpened();
	EXPORT int CALL GetScreenWidth();
	EXPORT int CALL GetScreenHeight();
	EXPORT int CALL GetScreenFPS();
	EXPORT int CALL GetDesktopWidth();
	EXPORT int CALL GetDesktopHeight();
	EXPORT float CALL GetDelta();
}
