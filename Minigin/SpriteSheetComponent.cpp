#include "SpriteSheetComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

namespace dae
{
    SpriteSheetComponent::SpriteSheetComponent(GameObject* ownerPtr, const std::string& filename, int spriteWidth, float frameTime)
        : TextureComponent(ownerPtr, filename)
        , m_SpriteWidth(spriteWidth)
        , m_FrameTime(frameTime)
        , m_ElapsedTime(0.0f)
        , m_CurrentFrame(0)
    {
        const auto textureSize = GetTexture()->GetSize();
        m_TotalFrames = textureSize.x / m_SpriteWidth;
    }

    void SpriteSheetComponent::Update(float deltaTime)
    {
        m_ElapsedTime += deltaTime;

        if (m_ElapsedTime >= m_FrameTime)
        {
            m_ElapsedTime -= m_FrameTime;
            m_CurrentFrame = (m_CurrentFrame + 1) % m_TotalFrames;
        }
		dae::TextureComponent::Update(deltaTime);
    }

    void SpriteSheetComponent::Render() const
    {
        dae::TextureComponent::Render();
    }

	void SpriteSheetComponent::SetSpriteSheet(const std::string& filename, const SDL_Rect* srcRect)
	{
		TextureComponent::SetTexture(filename, srcRect);

        const auto textureSize = GetTexture()->GetSize();
		m_TotalFrames = textureSize.x / m_SpriteWidth;
	}

    void SpriteSheetComponent::SetSpriteWidth(int spriteWidth)
    {
        m_SpriteWidth = spriteWidth;
        const auto textureSize = GetTexture()->GetSize();
        m_TotalFrames = textureSize.x / m_SpriteWidth;
    }

    void SpriteSheetComponent::SetFrameTime(float frameTime)
    {
        m_FrameTime = frameTime;
    }

    void SpriteSheetComponent::SetCurrentFrame(int frame)
    {
        if (frame >= 0 && frame < m_TotalFrames)
        {
            m_CurrentFrame = frame;
        }
    }
}