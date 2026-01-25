#include "../interface/scene_manager.h"
#include "engine_internal.h"
#include "scene.h"

extern "C"
{
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

	EXPORT float CALL GetResultX()
	{
		return GetEngine().sceneManager().resultX();
	}

	EXPORT float CALL GetResultY()
	{
		return GetEngine().sceneManager().resultY();
	}

	EXPORT float CALL GetResultZ()
	{
		return GetEngine().sceneManager().resultZ();
	}
}
