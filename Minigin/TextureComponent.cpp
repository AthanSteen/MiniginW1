#include "TextureComponent.h"
#include <string>
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

namespace dae
{
	TextureComponent::TextureComponent(GameObject* ownerPtr, const std::string& filename)
		: Component(ownerPtr), m_texture(nullptr)
	{
		SetTexture(filename);
	}

	void TextureComponent::Update(float deltaTime)
	{
		(void)deltaTime;
	}

	void TextureComponent::Render() const
	{
		if (m_texture)
		{
			const auto& pos = GetOwner()->GetWorldTransform().GetPosition() + m_localTransform.GetPosition();
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
		}
	}

	void TextureComponent::SetTexture(const std::string& filename)
	{
		m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

	void TextureComponent::SetLocalPosition(float x, float y)
	{
		m_localTransform.SetPosition(x, y, 0.0f);
	}
}