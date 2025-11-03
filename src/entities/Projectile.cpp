#include "Projectile.h"

bool Projectile::init()
{
    const sf::Texture* pTexture = ResourceManager::getOrLoadTexture("gem_orange.png");
    if (pTexture == nullptr)
        return false;

    m_pSprite = std::make_unique<sf::Sprite>(*pTexture);
    if (!m_pSprite)
        return false;

    sf::FloatRect localBounds = m_pSprite->getLocalBounds();
    m_pSprite->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
    m_pSprite->setPosition(m_position);
    m_pSprite->setScale(sf::Vector2f(2.5f, 2.5f));
	m_collisionRadius = m_pSprite->getGlobalBounds().getCenter().x;

    return true;
}

void Projectile::update(float dt)
{
	if (isSpawned)
		m_position += velocity * dt;
	if (m_position.x < -30 || m_position.y > 1100)
		despawn();
}

void Projectile::render(sf::RenderTarget& target) const
{
	if (isSpawned)
	{
		m_pSprite->setPosition(m_position);
		target.draw(*m_pSprite);
	}
}

void Projectile::spawn(sf::Vector2f source, sf::Vector2f target)
{
	velocity = (target - source).normalized() * 300.f;
	setPosition(source);
	isSpawned = true;
}

void Projectile::despawn(void)
{
	setPosition({-1000.f, -1000.f});
	isSpawned = false;
}
