#pragma once

#include "common.h"

struct Font;

extern "C"
{
	EXPORT Font *CALL LoadFont(const char *filename, int height);
	EXPORT void CALL FreeFont(Font *font);
	EXPORT int CALL GetTextWidth(Font *font, const char *text);
	EXPORT int CALL GetTextHeight(Font *font, const char *text);
}
