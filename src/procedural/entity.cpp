#include "../interface/entity_manager.h"
#include "engine_internal.h"
#include "entity.h"

struct Entity;
struct Material;

extern "C"
{
	EXPORT Entity *CALL CreateEntity()
	{
		return GetEngine().entityManager().createEntity();
	}

	EXPORT void CALL FreeEntity(Entity *entity)
	{
		GetEngine().entityManager().freeEntity(entity);
	}

	EXPORT const char *CALL GetEntityType(Entity *entity)
	{
		return GetEngine().entityManager().entityType(entity);
	}

	EXPORT void CALL SetEntityName(Entity *entity, const char *name)
	{
		GetEngine().entityManager().entityName(entity, name);
	}

	EXPORT const char *CALL GetEntityName(Entity *entity)
	{
		return GetEngine().entityManager().entityName(entity);
	}

	EXPORT void CALL SetEntityVisible(Entity *entity, bool_t visible)
	{
		GetEngine().entityManager().entityVisible(entity, visible);
	}

	EXPORT bool_t CALL IsEntityVisible(Entity *entity)
	{
		return GetEngine().entityManager().entityVisible(entity);
	}

	EXPORT void CALL SetEntityParent(Entity *entity, Entity *parent)
	{
		GetEngine().entityManager().entityParent(entity, parent);
	}

	EXPORT Entity *CALL GetEntityParent(Entity *entity)
	{
		return GetEngine().entityManager().entityParent(entity);
	}

	EXPORT int CALL GetEntityNumChildren(Entity *entity)
	{
		return GetEngine().entityManager().entityNumChildren(entity);
	}

	EXPORT Entity *CALL EntityChild(Entity *entity, int index)
	{
		return GetEngine().entityManager().entityChild(entity, index);
	}

	EXPORT void CALL SetEntityPosition(Entity *entity, float x, float y, float z)
	{
		GetEngine().entityManager().positionEntity(entity, x, y, z);
	}

	EXPORT void CALL MoveEntity(Entity *entity, float x, float y, float z)
	{
		GetEngine().entityManager().moveEntity(entity, x, y, z);
	}

	EXPORT void CALL TranslateEntity(Entity *entity, float x, float y, float z)
	{
		GetEngine().entityManager().translateEntity(entity, x, y, z);
	}

	EXPORT float CALL GetEntityX(Entity *entity)
	{
		return GetEngine().entityManager().entityX(entity);
	}

	EXPORT float CALL GetEntityY(Entity *entity)
	{
		return GetEngine().entityManager().entityY(entity);
	}

	EXPORT float CALL GetEntityZ(Entity *entity)
	{
		return GetEngine().entityManager().entityZ(entity);
	}

	EXPORT float CALL GetEntityLocalX(Entity *entity)
	{
		return GetEngine().entityManager().entityLocalX(entity);
	}

	EXPORT float CALL GetEntityLocalY(Entity *entity)
	{
		return GetEngine().entityManager().entityLocalY(entity);
	}
	EXPORT float CALL GetEntityLocalZ(Entity *entity)
	{
		return GetEngine().entityManager().entityLocalZ(entity);
	}

	EXPORT void CALL SetEntityRotation(Entity *entity, float pitch, float yaw, float roll)
	{
		GetEngine().entityManager().rotateEntity(entity, pitch, yaw, roll);
	}

	EXPORT void CALL TurnEntity(Entity *entity, float pitch, float yaw, float roll)
	{
		GetEngine().entityManager().turnEntity(entity, pitch, yaw, roll);
	}

	EXPORT void CALL PointEntity(Entity *entity, float x, float y, float z)
	{
		GetEngine().entityManager().pointEntity(entity, x, y, z);
	}

	EXPORT float CALL GetEntityPitch(Entity *entity)
	{
		return GetEngine().entityManager().entityPitch(entity);
	}

	EXPORT float CALL GetEntityYaw(Entity *entity)
	{
		return GetEngine().entityManager().entityYaw(entity);
	}

	EXPORT float CALL GetEntityRoll(Entity *entity)
	{
		return GetEngine().entityManager().entityRoll(entity);
	}

	EXPORT void CALL SetEntityScale(Entity *entity, float x, float y, float z)
	{
		GetEngine().entityManager().scaleEntity(entity, x, y, z);
	}

	EXPORT float CALL GetEntityScaleX(Entity *entity)
	{
		return GetEngine().entityManager().entityScaleX(entity);
	}

	EXPORT float CALL GetEntityScaleY(Entity *entity)
	{
		return GetEngine().entityManager().entityScaleY(entity);
	}

	EXPORT float CALL GetEntityScaleZ(Entity *entity)
	{
		return GetEngine().entityManager().entityScaleZ(entity);
	}

	EXPORT float CALL GetEntityWidth(Entity *entity)
	{
		return GetEngine().entityManager().entityWidth(entity);
	}

	EXPORT float CALL GetEntityHeight(Entity *entity)
	{
		return GetEngine().entityManager().entityHeight(entity);
	}

	EXPORT float CALL GetEntityDepth(Entity *entity)
	{
		return GetEngine().entityManager().entityDepth(entity);
	}

	EXPORT int CALL GetEntityNumMaterials(Entity *entity)
	{
		return GetEngine().entityManager().entityNumMaterials(entity);
	}

	EXPORT Material *CALL GetEntityMaterial(Entity *entity, int index)
	{
		return GetEngine().entityManager().entityMaterial(entity, index);
	}

	EXPORT float CALL GetEntityDistance(Entity *entity, float x, float y, float z)
	{
		return GetEngine().entityManager().entityDistance(entity, x, y, z);
	}

	EXPORT float CALL GetEntitySquaredDistance(Entity *entity, float x, float y, float z)
	{
		return GetEngine().entityManager().entitySquaredDistance(entity, x, y, z);
	}
}
