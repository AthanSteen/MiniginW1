#include "TextComponent.h"
#include "Renderer.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "GameObject.h"


namespace dae
{
    TextComponent::TextComponent(GameObject* ownerPtr, const std::string& text, std::shared_ptr<Font> font)
        : Component(ownerPtr), 
        m_text(text), 
        m_font(std::move(font)),
        m_color{ SDL_Color{255,255,255,255} }
    {
    }

    void TextComponent::Update(float)
    {
        if (m_needsUpdate)
        {
            SDL_Surface* surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_color);
            if (!surf)
            {
                throw std::runtime_error("Render text failed: " + std::string(SDL_GetError()));
            }

            SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
            SDL_FreeSurface(surf);

            if (!texture)
            {
                throw std::runtime_error("Create text texture failed: " + std::string(SDL_GetError()));
            }

            m_textTexture = std::make_shared<Texture2D>(texture);
            m_needsUpdate = false;
        }
    }

    void TextComponent::Render() const
    {
        if (m_textTexture)
        {
            const auto& pos = GetOwner()->GetWorldTransform().GetPosition() + m_localTransform.GetPosition();
            Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
        }
    }

	void TextComponent::SetLocalPosition(float x, float y)
	{
		m_localTransform.SetPosition(x, y, 0.0f);
	}

    void TextComponent::SetText(const std::string& text)
    {
        if (m_text != text)
        {
            m_text = text;
            m_needsUpdate = true;
        }
    }

	void TextComponent::SetColor(const SDL_Color& color)
	{
        m_color = color; 
        m_needsUpdate = true;
	}
}
