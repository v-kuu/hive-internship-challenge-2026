#include "StatePlaying.h"
#include <cmath>
#include "StatePaused.h"
#include "StateStack.h"
#include "ResourceManager.h"
#include <memory>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

StatePlaying::StatePlaying(StateStack& stateStack)
    : m_stateStack(stateStack)
{
}

bool StatePlaying::init()
{
    m_ground.setSize({1024.0f, 256.0f});
    m_ground.setPosition({0.0f, 800.0f});
    m_ground.setFillColor(sf::Color::Green);

    m_pPlayer = std::make_unique<Player>();
	m_UI = std::make_unique<UserInterface>(*m_pPlayer);
    if (!m_pPlayer || !m_pPlayer->init() || !m_UI->init())
        return false;
	for (int i = 0; i < 32; ++i)
	{
		std::unique_ptr<Enemy> pEnemy = std::make_unique<Enemy>();
		if (pEnemy->init())
			m_enemies.push_back(std::move(pEnemy));
	}
    m_pPlayer->setPosition(sf::Vector2f(200, 800));

    return true;
}

void StatePlaying::update(float dt)
{
    m_timeUntilEnemySpawn -= dt;

    if (m_timeUntilEnemySpawn < 0.0f)
    {
		if (nextEnemy == m_enemies.size())
			nextEnemy = 0;
		m_enemies[nextEnemy]->spawn();
		nextEnemy++;
        m_timeUntilEnemySpawn = enemySpawnInterval;
    }

    bool isPauseKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    m_hasPauseKeyBeenReleased |= !isPauseKeyPressed;
    if (m_hasPauseKeyBeenReleased && isPauseKeyPressed)
    {
        m_hasPauseKeyBeenReleased = false;
        m_stateStack.push<StatePaused>();
    }

    m_pPlayer->update(dt);

    for (const std::unique_ptr<Enemy>& pEnemy : m_enemies)
    {
        pEnemy->update(dt);
    }

    // Detect collisions
    bool playerDied = false;
    for (const std::unique_ptr<Enemy>& pEnemy : m_enemies)
    {
        float distance = (m_pPlayer->getPosition() - pEnemy->getPosition()).lengthSquared();
        float minDistance = std::pow(Player::collisionRadius + pEnemy->getCollisionRadius(), 2.0f);
        const sf::Vector2f playerPosition = m_pPlayer->getPosition();

        if (distance <= minDistance)
        {
			int hpRemaining = m_pPlayer->getHealth() - 1;
			if (hpRemaining <= 0)
			{
				playerDied = true;
				break;
			}
			m_pPlayer->setHealth(hpRemaining);
			pEnemy->despawn();
        }
    }
	m_UI->update(dt);
    // End Playing State on player death
    if (playerDied)
        m_stateStack.popDeferred();
}

void StatePlaying::render(sf::RenderTarget& target) const
{
    target.draw(m_ground);
    for (const std::unique_ptr<Enemy>& pEnemy : m_enemies)
        pEnemy->render(target);
    m_pPlayer->render(target);
	m_UI->render(target);
}
