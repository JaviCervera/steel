#pragma once

struct Camera;

struct SceneManager
{
	virtual ~SceneManager() {}
	virtual void ambient(int color) = 0;
	virtual void drawScene(const Camera *camera) = 0;
	virtual void screenCoords(const Camera *camera, float x, float y, float z) = 0;
	virtual void sceneCoords(const Camera *camera, float x, float y, float depth) = 0;
	virtual float coordX() = 0;
	virtual float coordY() = 0;
	virtual float coordZ() = 0;
};
