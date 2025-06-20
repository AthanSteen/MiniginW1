#pragma once
#include <memory>
#include "Component.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"

namespace dae
{
    class TextureComponent : public Component
    {
    public:
        explicit TextureComponent(GameObject* ownerPtr, const std::string& filename);
        
        TextureComponent(const TextureComponent& other) = delete;
        TextureComponent(TextureComponent&& other) = delete;
        TextureComponent& operator=(const TextureComponent& other) = delete;
        TextureComponent& operator=(TextureComponent&& other) = delete;

        void Update(float deltaTime) override;
        void Render() const override;
        void SetLocalPosition(float x, float y) override;

        void SetTexture(const std::string& filename, const SDL_Rect* srcRect = nullptr);   
        std::shared_ptr<Texture2D> GetTexture() const { return m_texture; }

    private:
        Transform m_localTransform{};
        std::shared_ptr<Texture2D> m_texture;
		std::unique_ptr<SDL_Rect> m_srcRect;
    };
}
