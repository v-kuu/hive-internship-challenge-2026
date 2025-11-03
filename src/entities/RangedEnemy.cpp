#include "RangedEnemy.h"

bool RangedEnemy::init()
{
    const sf::Texture* pTexture = ResourceManager::getOrLoadTexture("some_yellow_thing.png");
    if (pTexture == nullptr)
        return false;

    m_pSprite = std::make_unique<sf::Sprite>(*pTexture);
    if (!m_pSprite)
        return false;

    sf::FloatRect localBounds = m_pSprite->getLocalBounds();
    m_pSprite->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
    m_pSprite->setPosition(m_position);
	m_pSprite->setRotation(sf::degrees(180));
    m_pSprite->setScale(sf::Vector2f(2.5f, 2.5f));

	for (int i = 0; i < 10; ++i)
	{
		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>();
		if (projectile->init())
			projectiles.push_back(std::move(projectile));
	}
    return true;
}

void RangedEnemy::update(float dt)
{
	if (isSpawned)
	{
		m_position.x -= 300 * dt;
		if (m_position.x < -30)
			despawn();
		if (fireCooldown > 0)
			fireCooldown -= dt;
	}
}

void RangedEnemy::render(sf::RenderTarget& target) const
{
	if (isSpawned)
	{
		m_pSprite->setPosition(m_position);
		target.draw(*m_pSprite);
	}
}

void RangedEnemy::spawn(void)
{
	setPosition({1100, 100});
	isSpawned = true;
	fireCooldown = 1.0f;
}

void RangedEnemy::despawn(void)
{
	setPosition({-1000.f, -1000.f});
	isSpawned = false;
}

void RangedEnemy::fire(sf::Vector2f target)
{
	if (fireCooldown <= 0 && isSpawned)
	{
		if (nextProjectile == projectiles.size())
			nextProjectile = 0;
		projectiles[0]->spawn(m_position, target);
		nextProjectile++;
		fireCooldown = 3.f;
	}
}
