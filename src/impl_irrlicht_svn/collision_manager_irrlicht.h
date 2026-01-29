#pragma once

#include "../interface/collision_manager.h"
#include "../interface/entity_manager.h"
#include "platform_irrlicht.h"

struct CollisionManagerIrrlicht : public CollisionManager
{
	CollisionManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform),
				m_entity_mgr(NULL),
				m_point(),
				m_colliders()
	{
	}

	void entityManager(EntityManager &entity_manager)
	{
		m_entity_mgr = &entity_manager;
	}

	void boxCollider(Entity *entity)
	{
		if (!entity)
			return;
		removeCollider(entity);
		irr::scene::ISceneNode *node = reinterpret_cast<irr::scene::ISceneNode *>(entity);
		irr::scene::ITriangleSelector *selector = scene().createTriangleSelectorFromBoundingBox(node);
		if (selector)
		{
			node->setTriangleSelector(selector);
			selector->drop();
			m_colliders.insert(node, selector);
		}
	}

	void modelCollider(Model *model)
	{
		if (!model)
			return;
		removeCollider(reinterpret_cast<Entity *>(model));
		irr::scene::IMeshSceneNode *node = reinterpret_cast<irr::scene::IMeshSceneNode *>(model);
		irr::scene::ITriangleSelector *selector = scene().createTriangleSelector(node->getMesh(), node);
		if (selector)
		{
			node->setTriangleSelector(selector);
			selector->drop();
			m_colliders.insert(node, selector);
		}
	}

	void animModelCollider(AnimModel *model)
	{
		if (!model)
			return;
		removeCollider(reinterpret_cast<Entity *>(model));
		irr::scene::IAnimatedMeshSceneNode *node = reinterpret_cast<irr::scene::IAnimatedMeshSceneNode *>(model);
		irr::scene::ITriangleSelector *selector = scene().createTriangleSelector(node->getMesh()->getMesh(0), node);
		if (selector)
		{
			node->setTriangleSelector(selector);
			selector->drop();
			m_colliders.insert(node, selector);
		}
	}

	void removeCollider(Entity *entity)
	{
		if (!entity)
			return;
		irr::scene::ISceneNode *node = reinterpret_cast<irr::scene::ISceneNode *>(entity);
		irr::scene::ITriangleSelector *selector = node->getTriangleSelector();
		if (selector)
		{
			node->setTriangleSelector(NULL);
			m_colliders.remove(node);
		}
	}

	bool hasCollider(Entity *entity) const
	{
		if (!entity)
			return false;
		irr::scene::ISceneNode *node = reinterpret_cast<irr::scene::ISceneNode *>(entity);
		return node->getTriangleSelector() != NULL;
	}

	void entityCollisionMask(Entity *entity, int mask)
	{
		if (entity)
			reinterpret_cast<irr::scene::ISceneNode *>(entity)->setID(mask);
	}

	int entityCollisionMask(const Entity *entity) const
	{
		return entity ? reinterpret_cast<const irr::scene::ISceneNode *>(entity)->getID() : 0;
	}

	Entity *slideEntity(
			Entity *entity,
			float x,
			float y,
			float z,
			float rad_x,
			float rad_y,
			float rad_z,
			int mask)
	{
		if (!entity || !m_entity_mgr)
			return NULL;
		irr::scene::ISceneNode *inode = reinterpret_cast<irr::scene::ISceneNode *>(entity);
		irr::scene::ISceneNode *col_node = NULL;
		for (ColliderMap::Iterator it = m_colliders.getIterator(); !it.atEnd(); it++)
		{
			ColliderMap::Node *map_node = it.getNode();
			irr::scene::ISceneNode *other_node = map_node->getKey();
			irr::scene::ITriangleSelector *other_collider = map_node->getValue();
			if ((other_node->getID() & mask) != 0 && other_collider != inode->getTriangleSelector())
			{
				const irr::core::vector3df radius(rad_x, rad_y, rad_z);
				irr::core::vector3df direction(x, y, z);
				irr::core::matrix4 m = irr::core::matrix4();
				m.setRotationDegrees(inode->getAbsoluteTransformation().getRotationDegrees());
				m.transformVect(direction);
				irr::core::triangle3df col_tri = irr::core::triangle3df();
				irr::core::vector3df col_point = irr::core::vector3df();
				bool is_falling = false;
				irr::core::vector3df result = collision().getCollisionResultPosition(
						other_collider,
						inode->getAbsolutePosition(),
						radius,
						direction,
						col_tri,
						col_point,
						is_falling,
						col_node);
				if (col_node != NULL)
				{
					// Has collided
					inode->setPosition(result);
					inode->updateAbsolutePosition();
					break;
				}
			}
		}
		if (col_node == NULL)
		{
			m_entity_mgr->moveEntity(entity, x, y, z);
		}
		return reinterpret_cast<Entity *>(col_node);
	}

	Entity *raycast(float x1, float y1, float z1, float x2, float y2, float z2, int mask)
	{
		for (ColliderMap::Iterator it = m_colliders.getIterator(); !it.atEnd(); it++)
		{
			ColliderMap::Node *map_node = it.getNode();
			irr::scene::ISceneNode *other_node = map_node->getKey();
			irr::scene::ITriangleSelector *other_collider = map_node->getValue();
			if ((other_node->getID() & mask) != 0)
			{
				const irr::core::line3df ray(
						irr::core::vector3df(x1, y1, z1),
						irr::core::vector3df(x2, y2, z2));
				irr::core::triangle3df col_tri;
				irr::scene::ISceneNode *col_node = NULL;
				if (collision().getCollisionPoint(
								ray,
								other_collider,
								m_point,
								col_tri,
								col_node))
				{
					return reinterpret_cast<Entity *>(col_node);
				}
			}
		}
		return NULL;
	}

	Entity *pickEntity(Camera *camera, float x, float y, int mask)
	{
		irr::scene::ICameraSceneNode *prev_active = scene().getActiveCamera();
		scene().setActiveCamera(reinterpret_cast<irr::scene::ICameraSceneNode *>(camera));
		irr::scene::ISceneNode *picked = collision().getSceneNodeFromScreenCoordinatesBB(irr::core::position2di(x, y), mask);
		scene().setActiveCamera(prev_active);
		return reinterpret_cast<Entity *>(picked);
	}

	float collisionPointX() const
	{
		return m_point.X;
	}

	float collisionPointY() const
	{
		return m_point.Y;
	}

	float collisionPointZ() const
	{
		return m_point.Z;
	}

private:
	typedef irr::core::map<irr::scene::ISceneNode *, irr::scene::ITriangleSelector *> ColliderMap;

	PlatformIrrlicht *m_platform;
	EntityManager *m_entity_mgr;
	irr::core::vector3df m_point;
	ColliderMap m_colliders;

	irr::scene::ISceneManager &scene()
	{
		return *m_platform->device().getSceneManager();
	}

	irr::scene::ISceneCollisionManager &collision()
	{
		return *scene().getSceneCollisionManager();
	}
};
