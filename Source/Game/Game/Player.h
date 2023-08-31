#pragma once
#include "Framework/Actor.h"
#include "Framework/PhysicsComponent.h"

namespace kiko
{
	class Player : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Player)

			bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float m_speed = 0;
		float m_turnRate = 0;
		float m_health = 100.0f;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}