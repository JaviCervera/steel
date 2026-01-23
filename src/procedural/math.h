#pragma once

#include "common.h"

extern "C"
{
	EXPORT float CALL Floor(float val);
	EXPORT float CALL Ceil(float val);
	EXPORT float CALL Abs(float val);
	EXPORT float CALL Sqr(float val);
	EXPORT float CALL Sin(float val);
	EXPORT float CALL Cos(float val);
	EXPORT float CALL Tan(float val);
	EXPORT float CALL ASin(float val);
	EXPORT float CALL ACos(float val);
	EXPORT float CALL ATan(float val);
	EXPORT float CALL ATan2(float x, float y);
	EXPORT float CALL Exp(float val);
	EXPORT float CALL Pow(float base, float exp);
	EXPORT float CALL Log(float val);
	EXPORT float CALL Log10(float val);
	EXPORT float CALL Min(float a, float b);
	EXPORT float CALL Max(float a, float b);
	EXPORT float CALL Clamp(float val, float min, float max);
	EXPORT int CALL BoolToInt(bool_t val);
	EXPORT int CALL Int(float val);
	EXPORT int CALL Rand(int min, int max);
	EXPORT void CALL RandSeed(int seed);
	EXPORT float CALL Deg(float rad);
	EXPORT float CALL Rad(float deg);
	EXPORT float CALL Wrap(float val, float mod);
}
