#pragma once
#include "Component.h"
#include "Core/Vector2.h"

namespace kiko
{
	class PhysicsComponent : Component
	{
	public:
		virtual void ApplyForce(const vec2& force) = 0;

	public:
		vec2 m_velocity;
		vec2 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;

		// Inherited via Component
		virtual void Update(float dt) override;
	};
}
