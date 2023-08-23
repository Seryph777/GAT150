#pragma once
#include "CollisionComponent.h"

namespace kiko
{
	class CircleCollisionComponent : CollisionComponent
	{
		CLASS_DECLARATION(CircleCollisionComponent)
		// Inherited via CollisionComponent
		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* collision) override;
	};
}