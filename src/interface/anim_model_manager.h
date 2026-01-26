#pragma once

#include "entity_manager.h"

struct AnimModel : public Entity
{
};

struct AnimModelManager
{
	virtual ~AnimModelManager() {};
	virtual AnimModel *loadAnimModel(const char *path) = 0;
	virtual AnimModel *copyAnimModel(const AnimModel *model) = 0;
	virtual void animModelLoopEnabled(AnimModel *model, bool enabled) = 0;
	virtual void animModelFps(AnimModel *model, float fps) = 0;
	virtual void animModelFrame(AnimModel *model, float frame) = 0;
	virtual float animModelFrame(const AnimModel *model) = 0;
	virtual void animModelFrameRange(AnimModel *model, float first, float last) = 0;
	virtual float animModelFirstFrame(const AnimModel *model) = 0;
	virtual float animModelLastFrame(const AnimModel *model) = 0;
};
