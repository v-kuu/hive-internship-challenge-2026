#pragma once

#include "Entity.h"
#include "ResourceManager.h"
#include "Player.h"
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>

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
		std::unique_ptr<sf::Text> _timerText;
		float _timeSurvived = 0;
		const Player &_player;

		std::string _timerString() const;
};
