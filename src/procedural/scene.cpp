#include "../interface/scene_manager.h"
#include "engine_internal.h"
#include "scene.h"

extern "C"
{
	EXPORT void CALL SetAmbient(int color)
	{
		GetEngine().sceneManager().ambient(color);
	}

	EXPORT void CALL SetFog(int color, float start, float end)
	{
		GetEngine().sceneManager().fog(color, start, end);
	}

	EXPORT void CALL DrawScene(const Camera *camera)
	{
		GetEngine().sceneManager().drawScene(camera);
	}

	EXPORT void CALL GetScreenCoords(const Camera *camera, float x, float y, float z)
	{
		GetEngine().sceneManager().screenCoords(camera, x, y, z);
	}

	EXPORT void CALL GetSceneCoords(const Camera *camera, float x, float y, float depth)
	{
		GetEngine().sceneManager().sceneCoords(camera, x, y, depth);
	}

	EXPORT float CALL GetCoordX()
	{
		return GetEngine().sceneManager().coordX();
	}

	EXPORT float CALL GetCoordY()
	{
		return GetEngine().sceneManager().coordY();
	}

	EXPORT float CALL GetCoordZ()
	{
		return GetEngine().sceneManager().coordZ();
	}
}
