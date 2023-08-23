#include "ModelRenderComponent.h"
#include "Actor.h"
#include "ResourceManager.h"

namespace kiko
{
	CLASS_DEFINITION(ModelRenderComponent)
		bool ModelRenderComponent::Initialize()
	{
		if (!modelName.empty()) m_model = GET_RESOURCE(Model, modelName, g_renderer);

		return true;
	}
	void kiko::ModelRenderComponent::Update(float dt)
	{

	}

	void kiko::ModelRenderComponent::Draw(Renderer& renderer)
	{
		//m_model->Draw(renderer, m_owner->m_transform);
	}

	void ModelRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, modelName);
	}
}
