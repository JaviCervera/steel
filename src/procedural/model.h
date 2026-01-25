#pragma once

#include "common.h"

struct Model;

extern "C"
{
	EXPORT Model *CALL CreateCubeModel();
	EXPORT Model *CALL CreateSphereModel();
}
