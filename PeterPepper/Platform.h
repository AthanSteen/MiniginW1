#pragma once
#include "Component.h"
#include "Transform.h"
#include "TextureComponent.h"
#include <memory>
#include <string>

namespace dae
{
	class Platform : public Component
    {
    public:
        explicit Platform(GameObject* ownerPtr);

        Platform(const Platform& other) = delete;
        Platform(Platform&& other) = delete;
        Platform& operator=(const Platform& other) = delete;
        Platform& operator=(Platform&& other) = delete;

        void Update(float deltaTime) override;
        void Render() const override;

        void SetLocalPosition(float x, float y) override;
        void GetWorldPosition(glm::vec2& outPos) const;
		void SetWidth(float width) { m_width = width; }
		float GetWidth() const { return m_width; }

        bool IsOverlapping(const glm::vec2& playerPos, const glm::vec2& playerSize) const;
    private:
        Transform m_localTransform;
        std::shared_ptr<Texture2D> m_texture;
		float m_width;
    };
}