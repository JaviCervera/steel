#pragma once

#include "entity_manager.h"

struct Light : public Entity
{
};

struct LightManager
{
	virtual ~LightManager() {}
	virtual Light *createDirectionalLight() = 0;
	virtual Light *createPointLight() = 0;
	virtual void lightDiffuse(Light *light, int color) = 0;
	virtual int lightDiffuse(const Light *light) const = 0;
	virtual void lightAmbient(Light *light, int color) = 0;
	virtual int lightAmbient(const Light *light) const = 0;
	virtual void lightSpecular(Light *light, int color) = 0;
	virtual int lightSpecular(const Light *light) const = 0;
	virtual void lightRadius(Light *light, float radius) = 0;
	virtual float lightRadius(const Light *light) const = 0;
};
