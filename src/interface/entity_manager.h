#pragma once

#include <stddef.h>

struct Entity
{
};

struct Material;

struct EntityManager
{
	virtual ~EntityManager() {}
	virtual Entity *createEntity() = 0;
	virtual void freeEntity(Entity *entity) = 0;
	virtual const char *entityType(const Entity *entity) = 0;
	virtual void entityName(Entity *entity, const char *name) = 0;
	virtual const char *entityName(const Entity *entity) = 0;
	virtual void entityVisible(Entity *entity, bool visible) = 0;
	virtual bool entityVisible(const Entity *entity) = 0;
	virtual void entityParent(Entity *entity, Entity *parent) = 0;
	virtual Entity *entityParent(Entity *entity) = 0;
	virtual size_t entityNumChildren(const Entity *entity) = 0;
	virtual Entity *entityChild(Entity *entity, size_t index) = 0;
	virtual void positionEntity(Entity *entity, float x, float y, float z) = 0;
	virtual void moveEntity(Entity *entity, float x, float y, float z) = 0;
	virtual void translateEntity(Entity *entity, float x, float y, float z) = 0;
	virtual float entityX(const Entity *entity) = 0;
	virtual float entityY(const Entity *entity) = 0;
	virtual float entityZ(const Entity *entity) = 0;
	virtual float entityLocalX(const Entity *entity) = 0;
	virtual float entityLocalY(const Entity *entity) = 0;
	virtual float entityLocalZ(const Entity *entity) = 0;
	virtual void rotateEntity(Entity *entity, float pitch, float yaw, float roll) = 0;
	virtual void turnEntity(Entity *entity, float pitch, float yaw, float roll) = 0;
	virtual void pointEntity(Entity *entity, float x, float y, float z) = 0;
	virtual float entityPitch(const Entity *entity) = 0;
	virtual float entityYaw(const Entity *entity) = 0;
	virtual float entityRoll(const Entity *entity) = 0;
	virtual void scaleEntity(Entity *entity, float x, float y, float z) = 0;
	virtual float entityScaleX(const Entity *entity) = 0;
	virtual float entityScaleY(const Entity *entity) = 0;
	virtual float entityScaleZ(const Entity *entity) = 0;
	virtual float entityWidth(const Entity *entity) = 0;
	virtual float entityHeight(const Entity *entity) = 0;
	virtual float entityDepth(const Entity *entity) = 0;
	virtual size_t entityNumMaterials(const Entity *entity) = 0;
	virtual Material *entityMaterial(Entity *entity, size_t index) = 0;
	virtual float entityDistance(const Entity *entity, float x, float y, float z) = 0;
	virtual float entitySquaredDistance(const Entity *entity, float x, float y, float z) = 0;
};
