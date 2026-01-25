#pragma once

#include "../interface/model_manager.h"
#include "platform_irrlicht.h"

struct ModelManagerIrrlicht : public ModelManager
{
	ModelManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform) {}

	Model *createCubeModel()
	{
		return reinterpret_cast<Model *>(scene().addCubeSceneNode(1));
	}

	Model *createSphereModel()
	{
		return reinterpret_cast<Model *>(scene().addSphereSceneNode(0.5f));
	}

private:
	PlatformIrrlicht *m_platform;

	irr::scene::ISceneManager &scene()
	{
		return *m_platform->device().getSceneManager();
	}
};
