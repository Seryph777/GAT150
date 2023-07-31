#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>

namespace kiko
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const Transform& transform) : m_transform{ transform } {}
		Actor(const Transform& transform, std::shared_ptr<kiko::Model> model) : m_transform{ transform }, m_model{ model } {}

		virtual void Update(float dt);
		virtual void Draw(Renderer& renderer);

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : (m_tag != "") ? 0 : -10000; }
		virtual void OnCollision(Actor* other) {};

		void AddForce(const vec2 force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		friend class Scene;
		friend class SpaceGame;

		Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;
	protected:
		class Scene* m_scene = nullptr;
		class Game* m_game = nullptr;
		bool m_destroyed = false;

		std::shared_ptr<Model> m_model;
		vec2 m_velocity;
		float m_damping = 0;
	};
}
