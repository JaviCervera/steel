#pragma once

#include "../interface/sprite_manager.h"
#include "platform_irrlicht.h"

struct SpriteManagerIrrlicht : public SpriteManager
{
	SpriteManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform) {}

	Sprite *createSprite(Texture *texture)
	{
		irr::video::ITexture *irr_texture = reinterpret_cast<irr::video::ITexture *>(texture);
		irr::scene::IBillboardSceneNode *sprite = m_platform->device().getSceneManager()->addBillboardSceneNode();
		sprite->getMaterial(0).MaterialType = irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL;
		sprite->getMaterial(0).TextureLayer[0].Texture = irr_texture;
		if (texture)
		{
			spriteSize(reinterpret_cast<Sprite *>(sprite),
								 irr_texture->getOriginalSize().Width,
								 irr_texture->getOriginalSize().Height);
		}
		else
		{
			spriteSize(reinterpret_cast<Sprite *>(sprite), 1.0f, 1.0f);
		}
		return reinterpret_cast<Sprite *>(sprite);
	}

	void spriteSize(Sprite *sprite, float width, float height)
	{
		if (!sprite)
			return;
		reinterpret_cast<irr::scene::IBillboardSceneNode *>(sprite)->setSize(
				irr::core::dimension2df(width, height));
	}

	float spriteWidth(const Sprite *sprite)
	{
		return sprite ? reinterpret_cast<irr::scene::IBillboardSceneNode *>(const_cast<Sprite *>(sprite))->getSize().Width : 0;
	}

	float spriteHeight(const Sprite *sprite)
	{
		return sprite ? reinterpret_cast<irr::scene::IBillboardSceneNode *>(const_cast<Sprite *>(sprite))->getSize().Height : 0;
	}

private:
	PlatformIrrlicht *m_platform;
};
