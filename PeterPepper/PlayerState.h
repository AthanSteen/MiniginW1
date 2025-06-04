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
	void ChangeState(State<PlayerState>* newState);

	dae::SpriteSheetComponent* GetSpriteSheet() const { return m_pTexture; };

private:
	std::unique_ptr<StateMachine<PlayerState>> m_StateMachine;
	dae::SpriteSheetComponent* m_pTexture;
};

class IdleState : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class WalkingState : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class ClimbingState : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class SprayState : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class HitState : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class DeadState : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class RespawnState : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};

class WinningState : public State<PlayerState>
{
public:
	void Enter(PlayerState* playerState) override;
	void Exit(PlayerState* playerState) override;
	void Update(PlayerState* playerState, float dt) override;
	void HandleInput(PlayerState* playerState) override;
};