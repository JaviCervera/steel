#pragma once

#include "entity_manager.h"

struct Model : public Entity
{
};

struct ModelManager
{
	virtual ~ModelManager() {}
	virtual Model *createCubeModel() = 0;
	virtual Model *createSphereModel() = 0;
};
