#pragma once

struct InputManager
{
	virtual ~InputManager() {}
	virtual void setMouseVisible(bool visible) = 0;
	virtual void setMousePosition(int x, int y) = 0;
	virtual int getMouseX() const = 0;
	virtual int getMouseY() const = 0;
	virtual int getMouseZ() const = 0;
	virtual bool isMouseButtonDown(int button) const = 0;
	virtual bool isMouseButtonHit(int button) const = 0;
	virtual bool isKeyDown(int key) const = 0;
	virtual bool isKeyHit(int key) const = 0;
};
