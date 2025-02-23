#pragma once
#include "Component.h"
#include <chrono>

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

    private:
        float m_fps = 0.f;
        TextComponent* m_textComponent;
    };
}
