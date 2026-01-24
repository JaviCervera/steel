#pragma once

#include "common.h"

struct Font;
struct Texture;

extern "C"
{
	EXPORT void CALL Cls(int color);
	EXPORT void CALL SetColor(int color);
	EXPORT void CALL DrawPlot(float x, float y);
	EXPORT void CALL DrawLine(float x1, float y1, float x2, float y2);
	EXPORT void CALL DrawRect(float x, float y, float width, float height);
	EXPORT void CALL DrawText(Font *font, const char *text, int x, int y);
	EXPORT void CALL DrawTexture(Texture *tex, float x, float y);
	EXPORT void CALL DrawTextureEx(Texture *tex, float x, float y, float width, float height);
	EXPORT void CALL DrawTextureRect(Texture *tex, float src_x, float src_y, float src_width, float src_height, float dst_x, float dst_y, float dst_width, float dst_height);
}
