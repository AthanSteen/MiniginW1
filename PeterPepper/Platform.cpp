#include "Platform.h"
#include "GameObject.h"
#include "ResourceManager.h"

namespace dae
{
	Platform::Platform(GameObject* ownerPtr) : 
        Component(ownerPtr),
		m_localTransform(),
		m_width(100.0f)
    {
		m_texture = ResourceManager::GetInstance().LoadTexture("Level/Platform.png");
    }

    void Platform::Update(float /*deltaTime*/)
    {

    }

    void Platform::Render() const
    {
        if (!m_texture) return;

        const auto pos = GetOwner()->GetWorldTransform().GetPosition() + m_localTransform.GetPosition();
        auto texSize = m_texture->GetSize();

        float x = pos.x;
        float y = pos.y;
        float step = static_cast<float>(texSize.x);

        for (float drawn = 0; drawn < m_width; drawn += step)
        {
            float drawW = std::min(step, m_width - drawn);
            SDL_Rect srcRect{ 0, 0, static_cast<int>(drawW), texSize.y };
            Renderer::GetInstance().RenderTexture(*m_texture, &srcRect, x + drawn, y, drawW, static_cast<float>(texSize.y));
        }
    }

    void Platform::SetLocalPosition(float x, float y)
    {
        m_localTransform.SetPosition(x, y, 0);
    }
}