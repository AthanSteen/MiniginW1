#pragma once
#include "Component.h"
#include "PlayerState.h"

class PlayerComponent : public dae::Component
{
public:
    explicit PlayerComponent(dae::GameObject* ownerPtr);

    void Update(float deltaTime) override;
    void Render() const override;
    void SetLocalPosition(float x, float y) override;

private:
    PlayerState m_PlayerState;
	std::unique_ptr<dae::SpriteSheetComponent> m_pSpriteSheet;
};