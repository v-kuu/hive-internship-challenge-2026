#include "Enemy.h"
#include "ResourceManager.h"
#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

bool Enemy::init()
{
    const sf::Texture* pTexture = ResourceManager::getOrLoadTexture("enemy.png");
    if (pTexture == nullptr)
        return false;

    m_pSprite = std::make_unique<sf::Sprite>(*pTexture);
    if (!m_pSprite)
        return false;

    sf::FloatRect localBounds = m_pSprite->getLocalBounds();
    m_pSprite->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
    m_pSprite->setPosition(m_position);
    m_pSprite->setScale(sf::Vector2f(2.5f, 2.5f));
    m_collisionRadius = collisionRadius;

    return true;
}

void Enemy::update(float dt)
{
	if (isSpawned)
		m_position.x -= 200 * dt;
	if (m_position.x < -30)
		despawn();
}

void Enemy::render(sf::RenderTarget& target) const
{
	if (isSpawned)
	{
		m_pSprite->setPosition(m_position);
		target.draw(*m_pSprite);
	}
}

void Enemy::spawn(void)
{
	setPosition({1100, 800});
	isSpawned = true;
}

void Enemy::despawn(void)
{
	setPosition({-1000.f, -1000.f});
	isSpawned = false;
}
