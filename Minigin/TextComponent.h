#pragma once

#include <string>
#include <memory>
#include "Component.h"
#include "Font.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae
{
    class TextComponent final : public Component
    {
    public:
        explicit TextComponent(GameObject* ownerPtr, const std::string& text, std::shared_ptr<Font> font);

        TextComponent(const TextComponent& other) = delete;
        TextComponent(TextComponent&& other) = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other) = delete;

        void Update(float deltaTime) override;
        void Render() const override;
        void SetLocalPosition(float x, float y) override;

        void SetText(const std::string& text);

    private:
        bool m_needsUpdate{ true };
        Transform m_localTransform{};
        std::string m_text;
        std::shared_ptr<Font> m_font;
        std::shared_ptr<Texture2D> m_textTexture;
    };
}
