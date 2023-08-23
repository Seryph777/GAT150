#pragma once
#include "PhysicsComponent.h"
#include "Actor.h"

namespace kiko
{
	class EnginePhysicsComponent : PhysicsComponent
	{
	public:



		// Inherited via PhysicsComponent
		virtual void Update(float dt) override;

		virtual void ApplyForce(const vec2& force) override;

	};
}