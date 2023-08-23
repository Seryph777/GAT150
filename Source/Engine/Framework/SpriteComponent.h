#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace kiko
{
	class SpriteComponent : RenderComponent
	{
	public:
		CLASS_DECLARATION(SpriteComponent)

	bool Initialize() override;
	void Update(float dt) override;
	void Draw(class Renderer& renderer) override;

	virtual float GetRadius() { return m_texture->GetSize().Length(); }

		

	public:
		std::string textureName;
		res_t<Texture> m_texture;
	};
}