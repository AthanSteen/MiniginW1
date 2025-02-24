#pragma once
#include "Component.h"
#include <chrono>
#include "Transform.h"

namespace dae
{
	class TextComponent;
    class FPSComponent : public Component
    {
    public:
        explicit FPSComponent(GameObject* ownerPtr, TextComponent* textComponent);

        FPSComponent(const FPSComponent& other) = delete;
        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;

        void Update(float deltaTime) override;
		void Render() const override;

        void SetLocalPosition(float x, float y) override;

    private:
        Transform m_localTransform{};
        float m_fps = 0.f;
        TextComponent* m_textComponent;
    };
}
