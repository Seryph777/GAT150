#pragma once
#include "Component.h"

namespace kiko
{
	class CollisionComponent : Component
	{
	public:
		virtual bool CheckCollision(CollisionComponent* collision) = 0;

	public:
		float m_radius = 0;

		// Inherited via Component
		virtual void Update(float dt) override;
	};
}