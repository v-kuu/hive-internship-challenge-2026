#pragma once

#include "Entity.h"
#include "ResourceManager.h"
#include <vector>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

class UserInterface final : public Entity
{
	public:
		UserInterface() = delete;
		UserInterface(const Player &player);
		virtual ~UserInterface() = default;

		bool init() override;
		void update(float dt) override;
		void render(sf::RenderTarget& target) const override;

	private:
		std::vector<sf::Sprite> _hpSprites;
		const Player &_player;
};
