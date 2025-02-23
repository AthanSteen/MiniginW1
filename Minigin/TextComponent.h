#pragma once

#include <string>
#include <memory>
#include "Component.h"
#include "Font.h"
#include "Texture2D.h"

namespace dae
{
    class TextComponent final : public Component
    {
    public:
        explicit TextComponent(GameObject* ownerPtr, const std::string& text, std::shared_ptr<Font> font);

        void Update(float deltaTime) override;
        void Render() const override;

        void SetText(const std::string& text);

    private:
        bool m_needsUpdate{ true };
        std::string m_text;
        std::shared_ptr<Font> m_font;
        std::shared_ptr<Texture2D> m_textTexture;
    };
}
