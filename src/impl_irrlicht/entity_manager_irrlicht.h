#pragma once

#include <math.h>
#include "../interface/entity_manager.h"
#include "platform_irrlicht.h"

struct EntityManagerIrrlicht : public EntityManager
{
	EntityManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform)
	{
	}

	Entity *createEntity()
	{
		return reinterpret_cast<Entity *>(scene().addEmptySceneNode());
	}

	void freeEntity(Entity *entity)
	{
		if (entity)
			reinterpret_cast<irr::scene::ISceneNode *>(entity)->remove();
	}

	const char *entityType(const Entity *entity)
	{
		if (!entity)
			return "";
		irr::core::map<irr::scene::ESCENE_NODE_TYPE, irr::core::stringc> types;
		types.set(irr::scene::ESNT_EMPTY, "Entity");
		types.set(irr::scene::ESNT_BILLBOARD, "Sprite");
		types.set(irr::scene::ESNT_CAMERA, "Camera");
		types.set(irr::scene::ESNT_PARTICLE_SYSTEM, "Emitter");
		types.set(irr::scene::ESNT_LIGHT, "Light");
		types.set(irr::scene::ESNT_MESH, "Model");
		types.set(irr::scene::ESNT_ANIMATED_MESH, "AnimModel");
		types.set(irr::scene::ESNT_OCT_TREE, "Octree");
		types.set(irr::scene::ESNT_TERRAIN, "Terrain");
		types.set(irr::scene::ESNT_WATER_SURFACE, "Water");
		return irr::core::stringc(types[reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getType()]).c_str();
	}

	void entityName(Entity *entity, const char *name)
	{
		if (entity)
			reinterpret_cast<irr::scene::ISceneNode *>(entity)->setName(name);
	}

	const char *entityName(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getName() : "";
	}

	void entityVisible(Entity *entity, bool visible)
	{
		if (entity)
			reinterpret_cast<irr::scene::ISceneNode *>(entity)->setVisible(visible);
	}

	bool entityVisible(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->isVisible() : false;
	}

	void entityParent(Entity *entity, Entity *parent)
	{
		if (entity)
			reinterpret_cast<irr::scene::ISceneNode *>(entity)->setParent(reinterpret_cast<irr::scene::ISceneNode *>(parent));
	}

	Entity *entityParent(Entity *entity)
	{
		return entity ? reinterpret_cast<Entity *>(reinterpret_cast<irr::scene::ISceneNode *>(entity)->getParent()) : NULL;
	}

	size_t entityNumChildren(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getChildren().getSize() : 0;
	}

	Entity *entityChild(Entity *entity, size_t index)
	{
		if (index >= entityNumChildren(entity))
			return NULL;
		return reinterpret_cast<Entity *>(*reinterpret_cast<irr::scene::ISceneNode *>(entity)->getChildren().begin() + index);
	}

	void positionEntity(Entity *entity, float x, float y, float z)
	{
		if (entity)
		{
			irr::scene::ISceneNode *irrent = reinterpret_cast<irr::scene::ISceneNode *>(entity);
			irrent->setPosition(irr::core::vector3df(x, y, z));
			irrent->updateAbsolutePosition();
		}
	}

	void moveEntity(Entity *entity, float x, float y, float z)
	{
		if (entity)
		{
			irr::scene::ISceneNode *irrent = reinterpret_cast<irr::scene::ISceneNode *>(entity);
			irr::core::vector3df dest(x, y, z);
			irrent->getRelativeTransformation().transformVect(dest);
			irrent->setPosition(dest);
			irrent->updateAbsolutePosition();
		}
	}

	void translateEntity(Entity *entity, float x, float y, float z)
	{
		if (entity)
		{
			irr::scene::ISceneNode *irrent = reinterpret_cast<irr::scene::ISceneNode *>(entity);
			irrent->setPosition(irrent->getPosition() + irr::core::vector3df(x, y, z));
			irrent->updateAbsolutePosition();
		}
	}

	float entityX(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getAbsolutePosition().X : 0;
	}

	float entityY(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getAbsolutePosition().Y : 0;
	}

	float entityZ(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getAbsolutePosition().Z : 0;
	}

	float entityLocalX(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getPosition().X : 0;
	}

	float entityLocalY(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getPosition().Y : 0;
	}

	float entityLocalZ(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getPosition().Z : 0;
	}

	void rotateEntity(Entity *entity, float pitch, float yaw, float roll)
	{
		if (entity)
		{
			irr::scene::ISceneNode *irrent = reinterpret_cast<irr::scene::ISceneNode *>(entity);
			irrent->setRotation(irr::core::vector3df(pitch, yaw, roll));
			if (irrent->getType() == irr::scene::ESNT_LIGHT && static_cast<irr::scene::ILightSceneNode *>(irrent)->getLightData().Type == irr::video::ELT_DIRECTIONAL)
			{
				irr::core::matrix4 mat;
				mat.setRotationDegrees(irr::core::vector3df(pitch, yaw, roll));
				irr::core::vector3df dest(0, 0, -1);
				mat.rotateVect(dest);
				const irr::core::vector3df final = irrent->getPosition() + dest;
				positionEntity(entity, final.X, final.Y, final.Z);
			}
		}
	}

	void turnEntity(Entity *entity, float pitch, float yaw, float roll)
	{
		if (entity)
		{
			irr::scene::ISceneNode *irrent = reinterpret_cast<irr::scene::ISceneNode *>(entity);
			rotateEntity(entity, irrent->getRotation().X + pitch, irrent->getRotation().Y + yaw, irrent->getRotation().Z + roll);
		}
	}

	void pointEntity(Entity *entity, float x, float y, float z)
	{
		if (entity)
		{
			irr::scene::ISceneNode *irrent = reinterpret_cast<irr::scene::ISceneNode *>(entity);
			const irr::core::vector3df diff = irrent->getAbsolutePosition() - irr::core::vector3df(x, y, z);
			const float distance = sqrtf(diff.X * diff.X + diff.Y * diff.Y + diff.Z * diff.Z);
			const float pitch = atan2(diff.Y, distance) * irr::core::RADTODEG;
			const float yaw = atan2(diff.X, -diff.Z) * irr::core::RADTODEG;
			rotateEntity(entity, pitch, yaw, irrent->getRotation().Z);
		}
	}

	float entityPitch(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getRotation().X : 0;
	}

	float entityYaw(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getRotation().Y : 0;
	}

	float entityRoll(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getRotation().Z : 0;
	}

	void scaleEntity(Entity *entity, float x, float y, float z)
	{
		if (entity)
			reinterpret_cast<irr::scene::ISceneNode *>(entity)->setScale(irr::core::vector3df(x, y, z));
	}

	float entityScaleX(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getScale().X : 0;
	}

	float entityScaleY(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getScale().Y : 0;
	}

	float entityScaleZ(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getScale().Z : 0;
	}

	float entityWidth(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getBoundingBox().getExtent().X : 0;
	}

	float entityHeight(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getBoundingBox().getExtent().Y : 0;
	}

	float entityDepth(const Entity *entity)
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getBoundingBox().getExtent().Z : 0;
	}

	size_t entityNumMaterials(const Entity *entity)
	{
		return entity ? reinterpret_cast<irr::scene::ISceneNode *>(const_cast<Entity *>(entity))->getMaterialCount() : 0;
	}

	Material *entityMaterial(Entity *entity, size_t index)
	{
		if (index >= entityNumMaterials(entity))
			return NULL;
		return reinterpret_cast<Material *>(&reinterpret_cast<irr::scene::ISceneNode *>(entity)->getMaterial(index));
	}

	float entityDistance(const Entity *entity, float x, float y, float z)
	{
		return reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getAbsolutePosition().getDistanceFrom(irr::core::vector3df(x, y, z));
	}

	float entitySquaredDistance(const Entity *entity, float x, float y, float z)
	{
		return reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getAbsolutePosition().getDistanceFromSQ(irr::core::vector3df(x, y, z));
	}

private:
	PlatformIrrlicht *m_platform;

	irr::scene::ISceneManager &scene()
	{
		return *m_platform->device().getSceneManager();
	}
};
