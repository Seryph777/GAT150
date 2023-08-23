#pragma once
#include "Object.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Framework/Component.h"
#include <memory>

namespace kiko
{
	class Actor : public Object
	{
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const Transform& transform) : transform{ transform } {}
		Actor(const Actor& other);

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(Renderer& renderer);
		template<typename T>
		T* GetComponent();
		

		void AddComponent(std::unique_ptr<Component> component);

		float GetRadius() { return 30.0f; }
		virtual void OnCollision(Actor* other) {};

		friend class Scene;
		friend class SpaceGame;
		class Scene* m_scene = nullptr;
		class Game* m_game = nullptr;

	public:
		Transform transform;
		std::string tag;
		float lifespan = -1.0f;
	protected:
		std::vector<std::unique_ptr<Component>> components;

		bool destroyed = false;
		bool persistent = false;
		bool prototype = false;
	};
	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}
