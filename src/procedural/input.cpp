#include "../interface/input_manager.h"
#include "engine_internal.h"
#include "input.h"

extern "C"
{
	EXPORT void CALL SetMouseVisible(bool_t visible)
	{
		GetEngine().inputManager().setMouseVisible(visible);
	}

	EXPORT void CALL SetMousePosition(int x, int y)
	{
		GetEngine().inputManager().setMousePosition(x, y);
	}

	EXPORT int CALL GetMouseX()
	{
		return GetEngine().inputManager().getMouseX();
	}

	EXPORT int CALL GetMouseY()
	{
		return GetEngine().inputManager().getMouseY();
	}

	EXPORT int CALL GetMouseZ()
	{
		return GetEngine().inputManager().getMouseZ();
	}

	EXPORT bool_t CALL IsMouseButtonDown(int button)
	{
		return GetEngine().inputManager().isMouseButtonDown(button);
	}

	EXPORT bool_t CALL IsMouseButtonHit(int button)
	{
		return GetEngine().inputManager().isMouseButtonHit(button);
	}

	EXPORT bool_t CALL IsKeyDown(int key)
	{
		return GetEngine().inputManager().isKeyDown(key);
	}

	EXPORT bool_t CALL IsKeyHit(int key)
	{
		return GetEngine().inputManager().isKeyHit(key);
	}
}
