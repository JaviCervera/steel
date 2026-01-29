#pragma once

#include "common.h"
#include "memblock.h"

struct Model;

extern "C"
{
	EXPORT Model *CALL CreateModel(const Memblock *data);
	EXPORT Model *CALL CreateCubeModel();
	EXPORT Model *CALL CreateSphereModel();
}
