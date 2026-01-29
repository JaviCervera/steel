#pragma once

#include "../interface/light_manager.h"
#include "platform_irrlicht.h"

struct LightManagerIrrlicht : public LightManager
{
	LightManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform) {}

	Light *createDirectionalLight()
	{
		irr::scene::ILightSceneNode *light = m_platform->device().getSceneManager()->addLightSceneNode();
		light->getLightData().Type = irr::video::ELT_DIRECTIONAL;
		return reinterpret_cast<Light *>(light);
	}

	Light *createPointLight()
	{
		irr::scene::ILightSceneNode *light = m_platform->device().getSceneManager()->addLightSceneNode();
		light->getLightData().Type = irr::video::ELT_POINT;
		return reinterpret_cast<Light *>(light);
	}

	void lightDiffuse(Light *light, int color)
	{
		if (!light)
			return;
		irr::scene::ILightSceneNode *irrlight = reinterpret_cast<irr::scene::ILightSceneNode *>(light);
		irrlight->getLightData().DiffuseColor = irr::video::SColor(color);
	}

	int lightDiffuse(const Light *light) const
	{
		if (!light)
			return 0;
		irr::scene::ILightSceneNode *irrlight = reinterpret_cast<irr::scene::ILightSceneNode *>(const_cast<Light *>(light));
		return irrlight->getLightData().DiffuseColor.toSColor().color;
	}

	void lightAmbient(Light *light, int color)
	{
		if (!light)
			return;
		irr::scene::ILightSceneNode *irrlight = reinterpret_cast<irr::scene::ILightSceneNode *>(light);
		irrlight->getLightData().AmbientColor = irr::video::SColor(color);
	}

	int lightAmbient(const Light *light) const
	{
		if (!light)
			return 0;
		irr::scene::ILightSceneNode *irrlight = reinterpret_cast<irr::scene::ILightSceneNode *>(const_cast<Light *>(light));
		return irrlight->getLightData().AmbientColor.toSColor().color;
	}

	void lightSpecular(Light *light, int color)
	{
		if (!light)
			return;
		irr::scene::ILightSceneNode *irrlight = reinterpret_cast<irr::scene::ILightSceneNode *>(light);
		irrlight->getLightData().SpecularColor = irr::video::SColor(color);
	}

	int lightSpecular(const Light *light) const
	{
		if (!light)
			return 0;
		irr::scene::ILightSceneNode *irrlight = reinterpret_cast<irr::scene::ILightSceneNode *>(const_cast<Light *>(light));
		return irrlight->getLightData().SpecularColor.toSColor().color;
	}

	void lightRadius(Light *light, float radius)
	{
		if (!light)
			return;
		irr::scene::ILightSceneNode *irrlight = reinterpret_cast<irr::scene::ILightSceneNode *>(light);
		irrlight->getLightData().Radius = radius;
	}

	float lightRadius(const Light *light) const
	{
		if (!light)
			return 0;
		irr::scene::ILightSceneNode *irrlight = reinterpret_cast<irr::scene::ILightSceneNode *>(const_cast<Light *>(light));
		return irrlight->getLightData().Radius;
	}

private:
	PlatformIrrlicht *m_platform;
};
