#pragma once

#include "Entity.h"
#include "ShaderBank.h"
#include <memory>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf { class Sprite; }

class Player final : public Entity
{
public:
    static constexpr float collisionRadius = 42.0f;
	static bool jumpInput;
	static bool deflectInput;

    Player();
    virtual ~Player() = default;
    
    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;
	void deflect(void);

	int m_maxHp = 3;
	float m_deflectCooldown = 0.f;
	bool m_isDeflecting = false;
	bool m_jumpAvailable = true;
	const float m_startVelocity = 600.f;
	float m_velocity_Y = 0.f;
	bool m_deflectInputGrace = false;
};
