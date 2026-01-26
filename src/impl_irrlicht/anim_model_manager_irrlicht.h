#pragma once

#include "../interface/anim_model_manager.h"
#include "platform_irrlicht.h"

struct AnimModelManagerIrrlicht : public AnimModelManager
{
	AnimModelManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform) {}

	AnimModel *loadAnimModel(const char *path)
	{
		irr::scene::IAnimatedMesh *mesh = m_platform->device().getSceneManager()->getMesh(path);
		if (!mesh)
			return NULL;
		return reinterpret_cast<AnimModel *>(m_platform->device().getSceneManager()->addAnimatedMeshSceneNode(mesh));
	}

	AnimModel *copyAnimModel(const AnimModel *model)
	{
		if (!model)
			return NULL;
		irr::scene::IAnimatedMeshSceneNode *orig_model = reinterpret_cast<irr::scene::IAnimatedMeshSceneNode *>(const_cast<AnimModel *>(model));
		irr::scene::IAnimatedMeshSceneNode *new_model = m_platform->device().getSceneManager()->addAnimatedMeshSceneNode(orig_model->getMesh());
		return reinterpret_cast<AnimModel *>(new_model);
	}

	void animModelLoopEnabled(AnimModel *model, bool enabled)
	{
		if (!model)
			return;
		reinterpret_cast<irr::scene::IAnimatedMeshSceneNode *>(model)->setLoopMode(enabled);
	}

	void animModelFps(AnimModel *model, float fps)
	{
		if (!model)
			return;
		reinterpret_cast<irr::scene::IAnimatedMeshSceneNode *>(model)->setAnimationSpeed(fps);
	}

	void animModelFrame(AnimModel *model, float frame)
	{
		if (!model)
			return;
		reinterpret_cast<irr::scene::IAnimatedMeshSceneNode *>(model)->setCurrentFrame(frame);
	}

	float animModelFrame(const AnimModel *model)
	{
		return model ? reinterpret_cast<const irr::scene::IAnimatedMeshSceneNode *>(model)->getFrameNr() : 0.0f;
	}

	void animModelFrameRange(AnimModel *model, float first, float last)
	{
		if (!model)
			return;
		reinterpret_cast<irr::scene::IAnimatedMeshSceneNode *>(model)->setFrameLoop(static_cast<irr::s32>(first), static_cast<irr::s32>(last));
	}

	float animModelFirstFrame(const AnimModel *model)
	{
		return model ? reinterpret_cast<const irr::scene::IAnimatedMeshSceneNode *>(model)->getStartFrame() : 0.0f;
	}

	float animModelLastFrame(const AnimModel *model)
	{
		return model ? reinterpret_cast<const irr::scene::IAnimatedMeshSceneNode *>(model)->getEndFrame() : 0.0f;
	}

private:
	PlatformIrrlicht *m_platform;
};
