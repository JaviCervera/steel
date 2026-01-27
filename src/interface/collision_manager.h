#pragma once

struct AnimModel;
struct Camera;
struct Entity;
struct Model;

struct CollisionManager
{
	virtual ~CollisionManager() {}
	virtual void boxCollider(Entity *entity) = 0;
	virtual void modelCollider(Model *model) = 0;
	virtual void animModelCollider(AnimModel *model) = 0;
	virtual void removeCollider(Entity *entity) = 0;
	virtual bool hasCollider(Entity *entity) const = 0;
	virtual void entityCollisionMask(Entity *entity, int mask) = 0;
	virtual int entityCollisionMask(const Entity *entity) const = 0;
	virtual Entity *slideEntity(
			Entity *entity,
			float x,
			float y,
			float z,
			float rad_x,
			float rad_y,
			float rad_z,
			int mask) = 0;
	virtual Entity *raycast(float x1, float y1, float z1, float x2, float y2, float z2, int mask) = 0;
	virtual Entity *pickEntity(Camera *camera, float x, float y, int mask) = 0;
	virtual float collisionPointX() const = 0;
	virtual float collisionPointY() const = 0;
	virtual float collisionPointZ() const = 0;
};
