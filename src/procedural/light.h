#pragma once

#include "common.h"

struct Light;

extern "C"
{
	EXPORT Light *CALL CreateDirectionalLight();
	EXPORT Light *CALL CreatePointLight();
	EXPORT void CALL SetLightDiffuse(Light *light, int color);
	EXPORT int CALL GetLightDiffuse(const Light *light);
	EXPORT void CALL SetLightAmbient(Light *light, int color);
	EXPORT int CALL GetLightAmbient(const Light *light);
	EXPORT void CALL SetLightSpecular(Light *light, int color);
	EXPORT int CALL GetLightSpecular(const Light *light);
	EXPORT void CALL SetLightRadius(Light *light, float radius);
	EXPORT float CALL GetLightRadius(const Light *light);
}
