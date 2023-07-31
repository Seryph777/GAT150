#pragma once
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"
#include "Game/SpaceGame.h"

class Player : public kiko::Actor {
public:
	Player(float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model}, 
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_damping = 0.99f;
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;


private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_health = 1000.0f;
};