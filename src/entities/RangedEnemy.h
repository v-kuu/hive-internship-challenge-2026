#pragma once

#include "Entity.h"
#include "Projectile.h"
#include <vector>

class RangedEnemy final : public Entity
{
	public:
		RangedEnemy() = default;
		virtual ~RangedEnemy() = default;

		bool init() override;
		void update(float dt) override;
		void render(sf::RenderTarget& target) const override;
		void spawn(void);
		void despawn(void);
		void fire(sf::Vector2f target);

		bool isSpawned = false;
		float fireCooldown = 0;
		std::vector<std::unique_ptr<Projectile>> projectiles;
		int nextProjectile = 0;
};
