#include "TextureComponent.h"
#include <string>
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include <iostream>

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
			if (m_srcRect)
			{
				Renderer::GetInstance().RenderTexture(*m_texture, m_srcRect.get(), pos.x, pos.y);
			}
			else
			{
				Renderer::GetInstance().RenderTexture(*m_texture, nullptr, pos.x, pos.y);
			}
		}
	}

	void TextureComponent::SetTexture(const std::string& filename, const SDL_Rect* srcRect)
	{
		auto texture = ResourceManager::GetInstance().LoadTexture(filename);
		if (!texture)
		{
			std::cerr << "Failed to load texture: " << filename << std::endl;
			return;
		}
		m_texture = texture;

		if (srcRect)
		{
			m_srcRect = std::make_unique<SDL_Rect>(*srcRect);
		}
		else
		{
			m_srcRect = nullptr;
		}
	}

	void TextureComponent::SetLocalPosition(float x, float y)
	{
		m_localTransform.SetPosition(x, y, 0.0f);
	}
}