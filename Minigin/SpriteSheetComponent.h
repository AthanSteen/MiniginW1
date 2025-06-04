#pragma once
#include "TextureComponent.h"
#include <memory>

namespace dae
{
    class SpriteSheetComponent : public TextureComponent
    {
    public:
        explicit SpriteSheetComponent(GameObject* ownerPtr, const std::string& filename, int spriteWidth, float frameTime);

        SpriteSheetComponent(const SpriteSheetComponent& other) = delete;
        SpriteSheetComponent(SpriteSheetComponent&& other) = delete;
        SpriteSheetComponent& operator=(const SpriteSheetComponent& other) = delete;
        SpriteSheetComponent& operator=(SpriteSheetComponent&& other) = delete;

        void Update(float deltaTime) override;
        void Render() const override;

		void SetSpriteSheet(const std::string& filename, const SDL_Rect* srcRect = nullptr);
        void SetSpriteWidth(int spriteWidth);
        void SetFrameTime(float frameTime);
        void SetCurrentFrame(int frame);

        std::shared_ptr<Texture2D> GetTexture() const { return m_texture; }
    private:
        int m_SpriteWidth;
        float m_FrameTime;
        float m_ElapsedTime;
        int m_CurrentFrame;
        int m_TotalFrames;
    };
}