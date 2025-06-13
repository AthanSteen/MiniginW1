#pragma once
#include "TextureComponent.h"
#include <memory>

namespace dae
{
    class SpriteSheetComponent : public Component
    {
    public:
        explicit SpriteSheetComponent(GameObject* ownerPtr, const std::string& filename, int spriteWidth, float frameTime);

        SpriteSheetComponent(const SpriteSheetComponent& other) = delete;
        SpriteSheetComponent(SpriteSheetComponent&& other) = delete;
        SpriteSheetComponent& operator=(const SpriteSheetComponent& other) = delete;
        SpriteSheetComponent& operator=(SpriteSheetComponent&& other) = delete;

        void Update(float deltaTime) override;
        void Render() const override;

		void SetSpriteSheet(const std::string& filename);
        void SetSpriteWidth(int spriteWidth);
        void SetFrameTime(float frameTime);
        void SetCurrentFrame(int frame);

        void SetMirror(bool toRight = false)
        {
            m_mirrorToRight = toRight;
        }

		void SetLocalPosition(float x, float y) override;
    private:
		void CalculateTotalFrames(); 
        std::shared_ptr<Texture2D> m_texture;

        int m_spriteWidth;
        float m_frameTime;
        float m_elapsedTime;
        int m_currentFrame;
        int m_totalFrames;
        bool m_mirrorToRight;
        Transform m_localTransform;

    };
}