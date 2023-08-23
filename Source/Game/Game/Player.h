#pragma once
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"
#include "Game/SpaceGame.h"
#include "Framework/PhysicsComponent.h"

class Player : public kiko::Actor {
public:
	Player(float speed, float turnRate, const kiko::Transform& transform) :
		Actor{ transform}, 
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		
	}

	bool Initialize() override;
	void Update(float dt) override;
	void OnCollision(Actor* other) override;


private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_health = 1000.0f;

	kiko::PhysicsComponent* m_physicsComponent = nullptr;
};