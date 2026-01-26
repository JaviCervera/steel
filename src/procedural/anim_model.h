#pragma once

#include "common.h"

struct AnimModel;

extern "C"
{
	EXPORT AnimModel *CALL LoadAnimModel(const char *path);
	EXPORT AnimModel *CALL CopyAnimModel(const AnimModel *model);
	EXPORT void CALL SetAnimModelLoopEnabled(AnimModel *model, bool_t enabled);
	EXPORT void CALL SetAnimModelFps(AnimModel *model, float fps);
	EXPORT void CALL SetAnimModelFrame(AnimModel *model, float frame);
	EXPORT float CALL GetAnimModelFrame(const AnimModel *model);
	EXPORT void CALL SetAnimModelFrameRange(AnimModel *model, float first, float last);
	EXPORT float CALL GetAnimModelFirstFrame(const AnimModel *model);
	EXPORT float CALL GetAnimModelLastFrame(const AnimModel *model);
}
