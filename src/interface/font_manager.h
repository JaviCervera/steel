#pragma once

struct Font;

struct FontManager
{
	virtual ~FontManager() {}
	virtual Font *loadFont(const char *filename, int height) = 0;
	virtual void freeFont(Font *font) = 0;
	virtual void drawText(const Font *font, const char *text, float x, float y) = 0;
	virtual int textWidth(const Font *font, const char *text) = 0;
	virtual int textHeight(const Font *font, const char *text) = 0;
};
