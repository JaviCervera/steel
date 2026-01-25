#pragma once

struct Camera;

struct SceneManager
{
	virtual ~SceneManager() {}
	virtual void drawScene(const Camera *camera) = 0;
	virtual void screenCoords(const Camera *camera, float x, float y, float z) = 0;
	virtual void sceneCoords(const Camera *camera, float x, float y, float depth) = 0;
	virtual float resultX() = 0;
	virtual float resultY() = 0;
	virtual float resultZ() = 0;
};
