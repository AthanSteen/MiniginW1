#pragma once
#include "State.h"
#include "StateMachine.h"
#include "SpriteSheetComponent.h"
#include <memory>

class PlayerState
{
public:
	PlayerState(dae::SpriteSheetComponent* spriteSheet);

	void Update(float dt);
	void HandleInput();
	void ChangeState(std::unique_ptr<State<PlayerState>> newState);

	dae::SpriteSheetComponent* GetSpriteSheet() const { return m_pTexture; };
	

private:
	std::unique_ptr<StateMachine<PlayerState>> m_StateMachine;
	dae::SpriteSheetComponent* m_pTexture;
};

class IdleState final : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class PlayerComponent;
class WalkingState final : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
private:
	PlayerComponent* m_playerComp = nullptr; // Pointer to PlayerComponent for walking state
};

class ClimbingState final : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class SprayState final : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class HitState final : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class DeadState final : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class RespawnState final : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class WinningState final : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};