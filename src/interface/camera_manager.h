#pragma once

struct Camera;

struct CameraManager
{
	virtual ~CameraManager() {}
	virtual Camera *createCamera() = 0;
	virtual void cameraRange(Camera *camera, float near_range, float far_range) = 0;
	virtual float cameraNearRange(const Camera *camera) = 0;
	virtual float cameraFarRange(const Camera *camera) = 0;
	virtual void cameraAspectRatio(Camera *camera, float aspect_ratio) = 0;
	virtual float cameraAspectRatio(const Camera *camera) = 0;
	virtual void cameraFov(Camera *camera, float fov) = 0;
	virtual float cameraFov(const Camera *camera) = 0;
};
