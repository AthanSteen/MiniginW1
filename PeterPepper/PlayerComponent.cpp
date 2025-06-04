#include "PlayerComponent.h"
#include "GameObject.h"

PlayerComponent::PlayerComponent(dae::GameObject* ownerPtr)
    : Component(ownerPtr),
	m_pSpriteSheet(std::make_unique<dae::SpriteSheetComponent>(ownerPtr, "PPIdle.png", 16, 0.1f)),
    m_PlayerState(m_pSpriteSheet.get())
{
}

void PlayerComponent::Update(float deltaTime)
{
    m_PlayerState.Update(deltaTime);
}

void PlayerComponent::Render() const
{
    if (auto spriteSheet = m_PlayerState.GetSpriteSheet())
    {
        spriteSheet->Render();
    }
}

void PlayerComponent::SetLocalPosition(float x, float y)
{
    // Delegate the position setting to the GameObject's transform
    GetOwner()->SetLocalPosition(x, y);
}