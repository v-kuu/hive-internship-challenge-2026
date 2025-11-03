#include "UserInterface.h"

UserInterface::UserInterface(const Player &player) : _player(player)
{
}

bool UserInterface::init()
{
	const sf::Texture* hpTexture = ResourceManager::getOrLoadTexture("heart_shaded.png");
	if (hpTexture == nullptr)
		return false;

	for (int i = 0; i < _player.getHealth(); ++i)
	{
		_hpSprites.emplace_back(*hpTexture);
		_hpSprites[i].setPosition({30.f + 40.f * i, 30.f});
		_hpSprites[i].setScale({4.f, 4.f});
	}
	return true;
}

void UserInterface::update(float dt)
{
	(void)dt;
}

void UserInterface::render(sf::RenderTarget& target) const
{
	for (int i = 0; i < _player.getHealth(); ++ i)
		target.draw(_hpSprites[i]);
}
