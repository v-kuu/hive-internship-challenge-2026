#pragma once

#include "IState.h"
#include "ShaderBank.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/RangedEnemy.h"
#include "entities/UserInterface.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class StatePlaying : public IState
{
public:
    StatePlaying(StateStack& stateStack);
    ~StatePlaying() = default;

    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

private:
    static constexpr const float enemySpawnInterval = 2.0f;
	static constexpr const float rangedSpawnInterval = 7.0f;
    float m_timeUntilEnemySpawn = enemySpawnInterval;
	float m_timeUntilRangedSpawn = rangedSpawnInterval;

    StateStack& m_stateStack;
    std::unique_ptr<Player> m_pPlayer;
	std::unique_ptr<RangedEnemy> m_rangedEnemy;
	std::unique_ptr<UserInterface> m_UI;
    std::vector<std::unique_ptr<Enemy>> m_enemies;
    sf::RectangleShape m_ground;
    bool m_hasPauseKeyBeenReleased = true;
	int m_nextEnemy = 0;
	float m_timeElapsed = 0;

    void updateCollisions();
};
