#include "Player.h"
#include "ResourceManager.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>

bool Player::jumpInput = false;

Player::Player()
{
}

bool Player::init()
{
    const sf::Texture* pTexture = ResourceManager::getOrLoadTexture("player.png");
    if (pTexture == nullptr)
        return false;

    m_pSprite = std::make_unique<sf::Sprite>(*pTexture);
    if (!m_pSprite)
        return false;

    m_rotation = sf::degrees(0);
    sf::FloatRect localBounds = m_pSprite->getLocalBounds();
    m_pSprite->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
    m_pSprite->setPosition(m_position);
    m_pSprite->setScale(sf::Vector2f(3.0f, 3.0f));
    m_collisionRadius = collisionRadius;
	setHealth(3);
    return true;
}

void Player::update(float dt)
{
	const float gravity = 800.f;

    if (jumpInput && m_jumpAvailable)
    {
		m_velocity_Y = m_startVelocity;
		m_jumpAvailable = false;
    }

    if (!jumpInput && m_velocity_Y >= 0)
		m_velocity_Y *= 0.9f * dt;

	m_velocity_Y -= gravity * dt;
	m_position.y -= m_velocity_Y * dt;
	if (m_position.y >= 800)
	{
		m_position.y = 800;
		m_jumpAvailable = true;
		m_velocity_Y = 0.f;
	}
}

void Player::render(sf::RenderTarget& target) const
{
    m_pSprite->setRotation(m_rotation);
    m_pSprite->setPosition(m_position);
    target.draw(*m_pSprite);
}
