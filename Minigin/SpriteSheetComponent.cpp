#include "SpriteSheetComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "iostream"

namespace dae
{
    SpriteSheetComponent::SpriteSheetComponent(GameObject* ownerPtr, const std::string& filename, int spriteWidth, float frameTime)
		: Component(ownerPtr)
        , m_spriteWidth(spriteWidth)
        , m_frameTime(frameTime)
		, m_elapsedTime(0.0f)
		, m_currentFrame(0)
		, m_localTransform()
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(filename);

        CalculateTotalFrames();
    }

    void SpriteSheetComponent::Update(float deltaTime)
    {
        m_elapsedTime += deltaTime;

        if (m_elapsedTime >= m_frameTime)
        {
            m_elapsedTime -= m_frameTime;
            m_currentFrame = (m_currentFrame + 1) % m_totalFrames;
        }
    }

    void SpriteSheetComponent::Render() const
    {
        if (!m_texture) return;

        SDL_Rect srcRect{};
        srcRect.x = m_currentFrame * m_spriteWidth;
        srcRect.y = 0;
        srcRect.w = m_spriteWidth;
        srcRect.h = m_texture->GetSize().y;

        const auto pos = GetOwner()->GetWorldTransform().GetPosition() + m_localTransform.GetPosition();
        Renderer::GetInstance().RenderTexture(*m_texture, &srcRect, pos.x, pos.y);
    }

	void SpriteSheetComponent::SetSpriteSheet(const std::string& filename)
	{
		auto test = ResourceManager::GetInstance().LoadTexture(filename);
		auto idk = test.use_count();
        if(idk > 1 && m_texture == test)
        {
            std::cout << "SpriteSheetComponent: Texture already loaded, use existing texture.\n";
            return;
        }
        m_texture.reset();
        m_texture = test;
        if (!m_texture)
        {
            std::cout << "SpriteSheetComponent: Failed to load texture: " << filename << "\n";
            m_totalFrames = 0;
            return;
        }

        CalculateTotalFrames();
	}

    void SpriteSheetComponent::SetSpriteWidth(int spriteWidth)
    {
        m_spriteWidth = spriteWidth;

        CalculateTotalFrames();
    }

    void SpriteSheetComponent::SetFrameTime(float frameTime)
    {
        m_frameTime = frameTime;
    }

    void SpriteSheetComponent::SetCurrentFrame(int frame)
    {
        if (frame >= 0 && frame < m_totalFrames)
        {
            m_currentFrame = frame;
        }
    }

    void SpriteSheetComponent::CalculateTotalFrames()
    {
		if (!m_texture)
		{
			std::cout << "Texture not initialized.\n";
			return;
		}

		const auto size = m_texture->GetSize();
		m_totalFrames = size.x / m_spriteWidth;
		if (m_totalFrames <= 0)
		{
			std::cout << "SpriteSheetComponent: Invalid sprite width or texture size.\n";
		}
    }

    void SpriteSheetComponent::SetLocalPosition(float x, float y)
    {
        m_localTransform.SetPosition(x, y, 0.0f);
    }
}