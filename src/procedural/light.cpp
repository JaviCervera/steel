#include "../interface/light_manager.h"
#include "engine_internal.h"
#include "light.h"

extern "C"
{
	EXPORT Light *CALL CreateDirectionalLight()
	{
		return GetEngine().lightManager().createDirectionalLight();
	}

	EXPORT Light *CALL CreatePointLight()
	{
		return GetEngine().lightManager().createPointLight();
	}

	EXPORT void CALL SetLightDiffuse(Light *light, int color)
	{
		GetEngine().lightManager().lightDiffuse(light, color);
	}

	EXPORT int CALL GetLightDiffuse(const Light *light)
	{
		return GetEngine().lightManager().lightDiffuse(light);
	}

	EXPORT void CALL SetLightAmbient(Light *light, int color)
	{
		GetEngine().lightManager().lightAmbient(light, color);
	}

	EXPORT int CALL GetLightAmbient(const Light *light)
	{
		return GetEngine().lightManager().lightAmbient(light);
	}

	EXPORT void CALL SetLightSpecular(Light *light, int color)
	{
		GetEngine().lightManager().lightSpecular(light, color);
	}

	EXPORT int CALL GetLightSpecular(const Light *light)
	{
		return GetEngine().lightManager().lightSpecular(light);
	}

	EXPORT void CALL SetLightRadius(Light *light, float radius)
	{
		GetEngine().lightManager().lightRadius(light, radius);
	}

	EXPORT float CALL GetLightRadius(const Light *light)
	{
		return GetEngine().lightManager().lightRadius(light);
	}
}
