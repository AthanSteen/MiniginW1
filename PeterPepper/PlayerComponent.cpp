#include "PlayerComponent.h"
#include "GameObject.h"
#include "BurgerPiece.h"

PlayerComponent::PlayerComponent(dae::GameObject* ownerPtr)
    : Component(ownerPtr),
	m_Owner(ownerPtr),
	m_pSpriteSheet(std::make_unique<dae::SpriteSheetComponent>(ownerPtr, "PPIdle.png", 16, 0.25f)),
    m_PlayerState(m_pSpriteSheet.get()),
	m_direction(0.0f, 0.0f),
	m_pLevel(nullptr),
	m_canMove(true)
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

		if (m_pLevel->AreAllBurgersMade())
		{
			m_PlayerState.ChangeState(std::make_unique<WinningState>());
		}
	}
}

void PlayerComponent::Move(float x, float y)
{
    if (!m_pLevel || (!x && !y) || !m_canMove) return;

    glm::vec3 currentPos = m_Owner->GetWorldTransform().GetPosition();
    glm::vec3 newPosition = currentPos;
    glm::vec2 playerSize{ m_pSpriteSheet->GetSpriteWidth(), m_pSpriteSheet->GetSpriteHeight() };

    // Horizontal movement
    if (x != 0.0f) {
        glm::vec2 testPos{ currentPos.x + x, currentPos.y };
        if (m_pLevel->isOverlappingPlatform(testPos, playerSize)) {
            newPosition.x += x;
        }
        // Clamp to level bounds
        float minX = 0.0f;
        float maxX = minX + 265.0f - playerSize.x;
        newPosition.x = std::clamp(newPosition.x, minX, maxX);
    }

    // Vertical movement (ladder)
    if (y != 0.0f) {
        glm::vec2 playerBottomPos{ currentPos.x + playerSize.x * 0.375f, currentPos.y + playerSize.y - 0.5f};
        glm::vec2 playerBottomSize{ playerSize.x * 0.25f, 1.0f};

		if (y > 0.0f) playerBottomSize.y += 1.5f;
		else playerBottomPos.y -= 1.5f;

        if (m_pLevel->isOverlappingLadders(playerBottomPos, playerBottomSize)) {
            newPosition.y += y;
        }
    }

    m_Owner->SetLocalPosition(newPosition.x, newPosition.y);
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