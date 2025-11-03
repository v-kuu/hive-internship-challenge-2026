#pragma once

#include "Entity.h"
#include <memory>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf { class Sprite; }

class Player final : public Entity
{
public:
    static constexpr float collisionRadius = 42.0f;
	static bool jumpInput;

    Player();
    virtual ~Player() = default;
    
    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

	bool m_jumpAvailable = true;
	const float m_startVelocity = 600.f;
	float m_velocity_Y = 0.f;
};
