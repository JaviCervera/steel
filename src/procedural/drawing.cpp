#include "../interface/font_manager.h"
#include "../interface/graphics_manager.h"
#include "engine_internal.h"
#include "drawing.h"

extern "C"
{
	EXPORT void CALL Cls(int color)
	{
		GetEngine().graphicsManager().cls(color);
	}

	EXPORT void CALL SetColor(int color)
	{
		GetEngine().graphicsManager().color(color);
	}

	EXPORT void CALL DrawPlot(float x, float y)
	{
		GetEngine().graphicsManager().plot(x, y);
	}

	EXPORT void CALL DrawLine(float x1, float y1, float x2, float y2)
	{
		GetEngine().graphicsManager().line(x1, y1, x2, y2);
	}

	EXPORT void CALL DrawRect(float x, float y, float width, float height)
	{
		GetEngine().graphicsManager().rect(x, y, width, height);
	}

	EXPORT void CALL DrawText(Font *font, const char *text, int x, int y)
	{
		GetEngine().fontManager().drawText(font, text, x, y);
	}

	EXPORT void CALL DrawTexture(Texture *tex, float x, float y)
	{
		GetEngine().graphicsManager().texture(tex, 0, 0, 0, 0, x, y, 0, 0);
	}

	EXPORT void CALL DrawTextureEx(Texture *tex, float x, float y, float width, float height)
	{
		GetEngine().graphicsManager().texture(tex, 0, 0, 0, 0, x, y, width, height);
	}

	EXPORT void CALL DrawTextureRect(Texture *tex, float src_x, float src_y, float src_width, float src_height, float dst_x, float dst_y, float dst_width, float dst_height)
	{
		GetEngine().graphicsManager().texture(tex, src_x, src_y, src_width, src_height, dst_x, dst_y, dst_width, dst_height);
	}
}
