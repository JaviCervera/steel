#include "../interface/input.h"
#include "engine_internal.h"
#include "input.h"

extern "C"
{
	EXPORT void CALL SetMouseVisible(bool_t visible)
	{
		GetEngine().input().setMouseVisible(visible);
	}

	EXPORT void CALL SetMousePosition(int x, int y)
	{
		GetEngine().input().setMousePosition(x, y);
	}

	EXPORT int CALL GetMouseX()
	{
		return GetEngine().input().getMouseX();
	}

	EXPORT int CALL GetMouseY()
	{
		return GetEngine().input().getMouseY();
	}

	EXPORT int CALL GetMouseZ()
	{
		return GetEngine().input().getMouseZ();
	}

	EXPORT bool_t CALL IsMouseButtonDown(int button)
	{
		return GetEngine().input().isMouseButtonDown(button);
	}

	EXPORT bool_t CALL IsMouseButtonHit(int button)
	{
		return GetEngine().input().isMouseButtonHit(button);
	}

	EXPORT bool_t CALL IsKeyDown(int key)
	{
		return GetEngine().input().isKeyDown(key);
	}

	EXPORT bool_t CALL IsKeyHit(int key)
	{
		return GetEngine().input().isKeyHit(key);
	}
}
