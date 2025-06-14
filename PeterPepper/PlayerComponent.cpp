#include "PlayerComponent.h"
#include "GameObject.h"
#include "BurgerPiece.h"

PlayerComponent::PlayerComponent(dae::GameObject* ownerPtr)
    : Component(ownerPtr),
	m_pSpriteSheet(std::make_unique<dae::SpriteSheetComponent>(ownerPtr, "PPIdle.png", 16, 0.1f)),
    m_PlayerState(m_pSpriteSheet.get()),
	m_direction(0.0f, 0.0f),
	m_pLevel(nullptr)
{
	m_pSpriteSheet->SetSpriteWidth(16);
}

void PlayerComponent::Update(float deltaTime)
{
	m_PlayerState.Update(deltaTime);
	if (m_pSpriteSheet)
		m_pSpriteSheet->Update(deltaTime);

	if (m_pLevel)
	{
		auto burgers = m_pLevel->GetBurgerPieces();
		for (auto& burger : burgers)
		{
			burger->CheckAndSetStepped(
				GetOwner()->GetWorldTransform().GetPosition(), 
				glm::vec2{	m_pSpriteSheet->GetSpriteWidth() , 
							m_pSpriteSheet->GetSpriteHeight() }
			);
		}
	}
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


void PlayerComponent::SetDirection(const glm::vec2& direction)
{
	if (m_direction == direction)
		return;

	m_direction = direction;

	if (m_direction.x != 0 || m_direction.y != 0)
	{
		m_PlayerState.ChangeState(std::make_unique<WalkingState>());
	}
}