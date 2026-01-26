#include "../interface/anim_model_manager.h"
#include "engine_internal.h"
#include "anim_model.h"

extern "C"
{
	EXPORT AnimModel *CALL LoadAnimModel(const char *path)
	{
		return GetEngine().animModelManager().loadAnimModel(path);
	}

	EXPORT AnimModel *CALL CopyAnimModel(const AnimModel *model)
	{
		return GetEngine().animModelManager().copyAnimModel(model);
	}

	EXPORT void CALL SetAnimModelLoopEnabled(AnimModel *model, bool_t enabled)
	{
		GetEngine().animModelManager().animModelLoopEnabled(model, enabled);
	}

	EXPORT void CALL SetAnimModelFps(AnimModel *model, float fps)
	{
		GetEngine().animModelManager().animModelFps(model, fps);
	}

	EXPORT void CALL SetAnimModelFrame(AnimModel *model, float frame)
	{
		GetEngine().animModelManager().animModelFrame(model, frame);
	}

	EXPORT float CALL GetAnimModelFrame(const AnimModel *model)
	{
		return GetEngine().animModelManager().animModelFrame(model);
	}

	EXPORT void CALL SetAnimModelFrameRange(AnimModel *model, float first, float last)
	{
		GetEngine().animModelManager().animModelFrameRange(model, first, last);
	}

	EXPORT float CALL GetAnimModelFirstFrame(const AnimModel *model)
	{
		return GetEngine().animModelManager().animModelFirstFrame(model);
	}

	EXPORT float CALL GetAnimModelLastFrame(const AnimModel *model)
	{
		return GetEngine().animModelManager().animModelLastFrame(model);
	}
}
