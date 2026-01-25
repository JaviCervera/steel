#pragma once

#include "common.h"

struct Camera;

extern "C"
{
	EXPORT void CALL DrawScene(const Camera *camera);
	EXPORT void CALL GetScreenCoords(const Camera *camera, float x, float y, float z);
	EXPORT void CALL GetSceneCoords(const Camera *camera, float x, float y, float depth);
	EXPORT float CALL GetResultX();
	EXPORT float CALL GetResultY();
	EXPORT float CALL GetResultZ();
}
