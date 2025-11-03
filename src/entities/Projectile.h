#pragma once

#include "Entity.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

class Projectile final : public Entity
{
	public:
		Projectile() = default;
		virtual ~Projectile() = default;

		bool init() override;
		void update(float dt) override;
		void render(sf::RenderTarget &target) const override;
		void spawn(sf::Vector2f source, sf::Vector2f target);
		void despawn(void);

		bool isSpawned = false;
		sf::Vector2f velocity = {};
};
