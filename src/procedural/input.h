#pragma once

#include "common.h"

extern "C"
{
	EXPORT void CALL SetMouseVisible(bool_t visible);
	EXPORT void CALL SetMousePosition(int x, int y);
	EXPORT int CALL GetMouseX();
	EXPORT int CALL GetMouseY();
	EXPORT int CALL GetMouseZ();
	EXPORT bool_t CALL IsMouseButtonDown(int button);
	EXPORT bool_t CALL IsMouseButtonHit(int button);
	EXPORT bool_t CALL IsKeyDown(int key);
	EXPORT bool_t CALL IsKeyHit(int key);
}
