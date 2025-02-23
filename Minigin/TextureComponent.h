#pragma once
#include <memory>
#include "Component.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"

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
        void SetTexture(const std::string& filename);

    private:
        std::shared_ptr<Texture2D> m_texture;
    };
}
