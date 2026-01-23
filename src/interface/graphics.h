#pragma once

#include "color.h"

struct Texture;

struct Graphics
{
	virtual ~Graphics() {};
	virtual void cls(int color = COLOR_BLACK) = 0;
	virtual void color(int color) = 0;
	virtual void plot(float x, float y) = 0;
	virtual void line(float x1, float y1, float x2, float y2) = 0;
	virtual void rect(float x, float y, float width, float height) = 0;
	virtual void texture(const Texture *tex, int src_x, int src_y, int src_width, int src_height, int dst_x, int dst_y, int dst_width, int dst_height) = 0;
};
