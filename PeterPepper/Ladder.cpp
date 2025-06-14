#include "Ladder.h"
#include "GameObject.h"
#include "ResourceManager.h"

namespace dae
{
    Ladder::Ladder(GameObject* ownerPtr) : 
        Component(ownerPtr),
        m_localTransform(),
		m_height(32.0f),
		m_width(12.0f)
    {
		m_texture = ResourceManager::GetInstance().LoadTexture("Level/Ladder.png");
		m_textureConnection = ResourceManager::GetInstance().LoadTexture("Level/LadderConnection.png");
    }

    void Ladder::Update(float /*deltaTime*/)
    {

    }

    void Ladder::Render() const
    {
        if (!m_texture || !m_textureConnection) return;

        const auto pos = GetOwner()->GetWorldTransform().GetPosition() + m_localTransform.GetPosition();
        auto ladderTexSize = m_texture->GetSize();
        auto connTexSize = m_textureConnection->GetSize();

        float x = pos.x;
        float y = pos.y;

        // Draw top connection
        Renderer::GetInstance().RenderTexture(*m_textureConnection, nullptr, x - 2, y, m_width + 4, static_cast<float>(connTexSize.y));

        // Draw ladder body (repeat)
        float bodyY = y + connTexSize.y;
        float bodyHeight = m_height - 2 * connTexSize.y;
        float ladderStep = static_cast<float>(ladderTexSize.y);
        for (float drawn = 0; drawn < bodyHeight; drawn += ladderStep)
        {
            float drawH = std::min(ladderStep, bodyHeight - drawn);
            SDL_Rect srcRect{ 0, 0, ladderTexSize.x, static_cast<int>(drawH) };
            Renderer::GetInstance().RenderTexture(*m_texture, &srcRect, x, bodyY + drawn, m_width, drawH);
        }

        // Draw bottom connection
        Renderer::GetInstance().RenderTexture(*m_textureConnection, nullptr, x - 2, y + m_height - connTexSize.y, m_width + 4, static_cast<float>(connTexSize.y));
    }

    void Ladder::SetLocalPosition(float x, float y)
    {
        m_localTransform.SetPosition(x, y, 0);
    }
}