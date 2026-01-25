#pragma once

#include "common.h"

struct Entity;
struct Material;

extern "C"
{
	EXPORT Entity *CALL CreateEntity();
	EXPORT void CALL FreeEntity(Entity *entity);
	EXPORT const char *CALL GetEntityType(Entity *entity);
	EXPORT void CALL SetEntityName(Entity *entity, const char *name);
	EXPORT const char *CALL GetEntityName(Entity *entity);
	EXPORT void CALL SetEntityVisible(Entity *entity, bool_t visible);
	EXPORT bool_t CALL IsEntityVisible(Entity *entity);
	EXPORT void CALL SetEntityParent(Entity *entity, Entity *parent);
	EXPORT Entity *CALL GetEntityParent(Entity *entity);
	EXPORT int CALL GetEntityNumChildren(Entity *entity);
	EXPORT Entity *CALL EntityChild(Entity *entity, int index);
	EXPORT void CALL SetEntityPosition(Entity *entity, float x, float y, float z);
	EXPORT void CALL MoveEntity(Entity *entity, float x, float y, float z);
	EXPORT void CALL TranslateEntity(Entity *entity, float x, float y, float z);
	EXPORT float CALL GetEntityX(Entity *entity);
	EXPORT float CALL GetEntityY(Entity *entity);
	EXPORT float CALL GetEntityZ(Entity *entity);
	EXPORT float CALL GetEntityLocalX(Entity *entity);
	EXPORT float CALL GetEntityLocalY(Entity *entity);
	EXPORT float CALL GetEntityLocalZ(Entity *entity);
	EXPORT void CALL SetEntityRotation(Entity *entity, float pitch, float yaw, float roll);
	EXPORT void CALL TurnEntity(Entity *entity, float pitch, float yaw, float roll);
	EXPORT void CALL PointEntity(Entity *entity, float x, float y, float z);
	EXPORT float CALL GetEntityPitch(Entity *entity);
	EXPORT float CALL GetEntityYaw(Entity *entity);
	EXPORT float CALL GetEntityRoll(Entity *entity);
	EXPORT void CALL SetEntityScale(Entity *entity, float x, float y, float z);
	EXPORT float CALL GetEntityScaleX(Entity *entity);
	EXPORT float CALL GetEntityScaleY(Entity *entity);
	EXPORT float CALL GetEntityScaleZ(Entity *entity);
	EXPORT float CALL GetEntityWidth(Entity *entity);
	EXPORT float CALL GetEntityHeight(Entity *entity);
	EXPORT float CALL GetEntityDepth(Entity *entity);
	EXPORT int CALL GetEntityNumMaterials(Entity *entity);
	EXPORT Material *CALL GetEntityMaterial(Entity *entity, int index);
	EXPORT float CALL GetEntityDistance(Entity *entity, float x, float y, float z);
	EXPORT float CALL GetEntitySquaredDistance(Entity *entity, float x, float y, float z);
}
