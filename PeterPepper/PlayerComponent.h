#pragma once
#include "Component.h"
#include "PlayerState.h"
#include "Level.h"

class PlayerComponent : public dae::Component
{
public:
    explicit PlayerComponent(dae::GameObject* ownerPtr);

    void Update(float deltaTime) override;
    void Render() const override;
    void SetLocalPosition(float x, float y) override;

    void SetDirection(const glm::vec2& direction);
	const glm::vec2& GetDirection() const { return m_direction; }

	void SetLevel(dae::Level * level) { m_pLevel = level; }

private:
	std::unique_ptr<dae::SpriteSheetComponent> m_pSpriteSheet;
    PlayerState m_PlayerState;
    dae::Level* m_pLevel;
    glm::vec2 m_direction;
};