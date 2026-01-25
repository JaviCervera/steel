#include "../interface/camera_manager.h"
#include "engine_internal.h"
#include "camera.h"

extern "C"
{
	EXPORT Camera *CALL CreateCamera()
	{
		return GetEngine().cameraManager().createCamera();
	}

	EXPORT void CALL SetCameraRange(Camera *cam, float near_range, float far_range)
	{
		GetEngine().cameraManager().cameraRange(cam, near_range, far_range);
	}

	EXPORT float CALL GetCameraNearRange(Camera *cam)
	{
		return GetEngine().cameraManager().cameraNearRange(cam);
	}

	EXPORT float CALL GetCameraFarRange(Camera *cam)
	{
		return GetEngine().cameraManager().cameraFarRange(cam);
	}

	EXPORT void CALL SetCameraAspectRatio(Camera *cam, float ratio)
	{
		GetEngine().cameraManager().cameraAspectRatio(cam, ratio);
	}

	EXPORT float CALL GetCameraAspectRatio(Camera *cam)
	{
		return GetEngine().cameraManager().cameraAspectRatio(cam);
	}

	EXPORT void CALL SetCameraFOV(Camera *cam, float fov)
	{
		GetEngine().cameraManager().cameraFov(cam, fov);
	}

	EXPORT float CALL GetCameraFOV(Camera *cam)
	{
		return GetEngine().cameraManager().cameraFov(cam);
	}
}
