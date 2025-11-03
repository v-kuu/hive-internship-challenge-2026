#include "UserInterface.h"

UserInterface::UserInterface(const Player &player) : _player(player)
{
}

bool UserInterface::init()
{
	const sf::Texture* hpTexture = ResourceManager::getOrLoadTexture("heart_shaded.png");
	const sf::Font* timerFont = ResourceManager::getOrLoadFont("Lavigne.ttf");
	if (hpTexture == nullptr || timerFont == nullptr)
		return false;

	_timerText = std::make_unique<sf::Text>(*timerFont);
	_timerText->setString(_timerString());
	_timerText->setStyle(sf::Text::Bold);
	sf::FloatRect localBounds = _timerText->getLocalBounds();
	_timerText->setOrigin({localBounds.size.x / 2.f, 0});

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
	_timeSurvived += dt;
	_timerText->setString(_timerString());
}

void UserInterface::render(sf::RenderTarget& target) const
{
	for (int i = 0; i < _player.getHealth(); ++ i)
		target.draw(_hpSprites[i]);
	_timerText->setPosition({target.getSize().x * 0.5f, 30.f});
	target.draw(*_timerText);
}

std::string UserInterface::_timerString() const
{
	std::stringstream timerStream;
	timerStream << std::fixed << std::setprecision(2);
	timerStream << "TIME SURVIVED: " << _timeSurvived << "s";
	return (timerStream.str());
}
