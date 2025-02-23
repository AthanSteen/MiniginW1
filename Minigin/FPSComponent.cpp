#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <iostream>

dae::FPSComponent::FPSComponent(GameObject* ownerPtr, TextComponent* textComponent)
    : Component(ownerPtr), m_fps(0), m_textComponent(textComponent) {}

void dae::FPSComponent::Update(float deltaTime)
{
    if (deltaTime > 0.0f) // Avoid division by zero
    {
        m_fps = 1.0f / deltaTime;
        std::cout << "FPS: " << m_fps << std::endl;
    }

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << m_fps;
    m_textComponent->SetText("FPS: " + stream.str());
}

void dae::FPSComponent::Render() const
{

}