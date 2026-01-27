#pragma once

#include "common.h"

struct AnimModel;
struct Camera;
struct Entity;
struct Model;

extern "C"
{
	EXPORT void CALL SetBoxCollider(Entity *entity);
	EXPORT void CALL SetModelCollider(Model *model);
	EXPORT void CALL SetAnimModelCollider(AnimModel *model);
	EXPORT void CALL RemoveCollider(Entity *entity);
	EXPORT bool_t CALL HasCollider(Entity *entity);
	EXPORT void CALL SetEntityCollisionMask(Entity *entity, int mask);
	EXPORT int CALL GetEntityCollisionMask(const Entity *entity);
	EXPORT Entity *CALL SlideEntity(
			Entity *entity,
			float x,
			float y,
			float z,
			float rad_x,
			float rad_y,
			float rad_z,
			int mask);
	EXPORT Entity *CALL Raycast(float x1, float y1, float z1, float x2, float y2, float z2, int mask);
	EXPORT Entity *CALL PickEntity(Camera *camera, float x, float y, int mask);
	EXPORT float CALL GetCollisionPointX();
	EXPORT float CALL GetCollisionPointY();
	EXPORT float CALL GetCollisionPointZ();
}
