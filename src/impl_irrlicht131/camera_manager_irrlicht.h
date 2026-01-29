#pragma once

#include "../interface/camera_manager.h"
#include "platform_irrlicht.h"

struct CameraManagerIrrlicht : public CameraManager
{
	CameraManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform) {}

	Camera *createCamera()
	{
		return reinterpret_cast<Camera *>(m_platform->device().getSceneManager()->addCameraSceneNode());
	}

	void cameraRange(Camera *camera, float near_range, float far_range)
	{
		if (!camera)
			return;
		irr::scene::ICameraSceneNode *icam = reinterpret_cast<irr::scene::ICameraSceneNode *>(camera);
		icam->setNearValue(near_range);
		icam->setFarValue(far_range);
	}

	float cameraNearRange(const Camera *camera)
	{
		return camera ? reinterpret_cast<irr::scene::ICameraSceneNode *>(const_cast<Camera *>(camera))->getNearValue() : 0.0f;
	}

	float cameraFarRange(const Camera *camera)
	{
		return camera ? reinterpret_cast<irr::scene::ICameraSceneNode *>(const_cast<Camera *>(camera))->getFarValue() : 0.0f;
	}

	void cameraAspectRatio(Camera *camera, float aspect_ratio)
	{
		if (!camera)
			return;
		reinterpret_cast<irr::scene::ICameraSceneNode *>(camera)->setAspectRatio(aspect_ratio);
	}

	float cameraAspectRatio(const Camera *camera)
	{
		return camera ? reinterpret_cast<irr::scene::ICameraSceneNode *>(const_cast<Camera *>(camera))->getAspectRatio() : 0.0f;
	}

	void cameraFov(Camera *camera, float fov)
	{
		if (!camera)
			return;
		reinterpret_cast<irr::scene::ICameraSceneNode *>(camera)->setFOV(fov * irr::core::DEGTORAD);
	}

	float cameraFov(const Camera *camera)
	{
		return camera
							 ? (reinterpret_cast<irr::scene::ICameraSceneNode *>(const_cast<Camera *>(camera))->getFOV() * irr::core::RADTODEG)
							 : 0.0f;
	}

private:
	PlatformIrrlicht *m_platform;
};
