#include "../interface/collision_manager.h"
#include "engine_internal.h"
#include "collision.h"

extern "C"
{
	EXPORT void CALL SetBoxCollider(Entity *entity)
	{
		GetEngine().collisionManager().boxCollider(entity);
	}

	EXPORT void CALL SetModelCollider(Model *model)
	{
		GetEngine().collisionManager().modelCollider(model);
	}

	EXPORT void CALL SetAnimModelCollider(AnimModel *model)
	{
		GetEngine().collisionManager().animModelCollider(model);
	}

	EXPORT void CALL RemoveCollider(Entity *entity)
	{
		GetEngine().collisionManager().removeCollider(entity);
	}

	EXPORT bool_t CALL HasCollider(Entity *entity)
	{
		return GetEngine().collisionManager().hasCollider(entity);
	}

	EXPORT void CALL SetEntityCollisionMask(Entity *entity, int mask)
	{
		GetEngine().collisionManager().entityCollisionMask(entity, mask);
	}

	EXPORT int CALL GetEntityCollisionMask(const Entity *entity)
	{
		return GetEngine().collisionManager().entityCollisionMask(entity);
	}

	EXPORT Entity *CALL SlideEntity(
			Entity *entity,
			float x,
			float y,
			float z,
			float rad_x,
			float rad_y,
			float rad_z,
			int mask)
	{
		return GetEngine().collisionManager().slideEntity(entity, x, y, z, rad_x, rad_y, rad_z, mask);
	}

	EXPORT Entity *CALL Raycast(float x1, float y1, float z1, float x2, float y2, float z2, int mask)
	{
		return GetEngine().collisionManager().raycast(x1, y1, z1, x2, y2, z2, mask);
	}

	EXPORT Entity *CALL PickEntity(Camera *camera, float x, float y, int mask)
	{
		return GetEngine().collisionManager().pickEntity(camera, x, y, mask);
	}

	EXPORT float CALL GetCollisionPointX()
	{
		return GetEngine().collisionManager().collisionPointX();
	}

	EXPORT float CALL GetCollisionPointY()
	{
		return GetEngine().collisionManager().collisionPointY();
	}

	EXPORT float CALL GetCollisionPointZ()
	{
		return GetEngine().collisionManager().collisionPointZ();
	}
}
