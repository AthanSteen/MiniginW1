#include "PlayerState.h"

PlayerState::PlayerState(dae::SpriteSheetComponent* spriteSheet) : m_StateMachine(std::make_unique<StateMachine<PlayerState>>()),
m_pTexture(spriteSheet)
{
	m_StateMachine->ChangeState(this, new IdleState());
}

void PlayerState::Update(float dt) {
    m_StateMachine->Update(this, dt);
}

void PlayerState::HandleInput() {
    m_StateMachine->HandleInput(this);
}

void PlayerState::ChangeState(State<PlayerState>* newState) {
    m_StateMachine->ChangeState(this, newState);
}


#pragma region Idle

void IdleState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPIdle.png");
}

void IdleState::Exit(PlayerState* playerState) {
	// Cleanup idle state
	(void)playerState;
}

void IdleState::Update(PlayerState* playerState, float dt) {
	// Update idle state
	(void)playerState;
	(void)dt;
}

void IdleState::HandleInput(PlayerState* playerState) {
	// Handle input for idle state
	(void)playerState;
}
#pragma endregion

#pragma region Walking
void WalkingState::Enter(PlayerState* playerState) {
	//TODO switch logic for direction
	playerState->GetSpriteSheet()->SetSpriteSheet("PPLeft.png");
}

void WalkingState::Exit(PlayerState* playerState) {
	// Cleanup walking state
	(void)playerState;
}

void WalkingState::Update(PlayerState* playerState, float dt) {
	// Update walking state
	(void)playerState;
	(void)dt;
}

void WalkingState::HandleInput(PlayerState* playerState) {
	// Handle input for walking state
	(void)playerState;
}
#pragma endregion

#pragma region Climbing
void ClimbingState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPUp.png");
}

void ClimbingState::Exit(PlayerState* playerState) {
	// Cleanup climbing state
	(void)playerState;
}

void ClimbingState::Update(PlayerState* playerState, float dt) {
	// Update climbing state
	(void)playerState;
	(void)dt;
}

void ClimbingState::HandleInput(PlayerState* playerState) {
	// Handle input for climbing state
	(void)playerState;
}
#pragma endregion

#pragma region Spray
void SprayState::Enter(PlayerState* playerState) {
	// Initialize spray state
	(void)playerState;
}

void SprayState::Exit(PlayerState* playerState) {
	// Cleanup spray state
	(void)playerState;
}

void SprayState::Update(PlayerState* playerState, float dt) {
	// Update spray state
	(void)playerState;
	(void)dt;
}

void SprayState::HandleInput(PlayerState* playerState) {
	// Handle input for spray state
	(void)playerState;
}
#pragma endregion

#pragma region Hit
void HitState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPHit.png");
}

void HitState::Exit(PlayerState* playerState) {
	// Cleanup hit state
	(void)playerState;
}

void HitState::Update(PlayerState* playerState, float dt) {
	// Update hit state
	(void)playerState;
	(void)dt;
}

void HitState::HandleInput(PlayerState* playerState) {
	// Handle input for hit state
	(void)playerState;
}
#pragma endregion

#pragma region Dead
void DeadState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPDead.png");
}

void DeadState::Exit(PlayerState* playerState) {
	// Cleanup hit state
	(void)playerState;
}

void DeadState::Update(PlayerState* playerState, float dt) {
	// Update hit state
	(void)playerState;
	(void)dt;
}

void DeadState::HandleInput(PlayerState* playerState) {
	// Handle input for hit state
	(void)playerState;
}
#pragma endregion

#pragma region Respawn
void RespawnState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPIdle.png");
}

void RespawnState::Exit(PlayerState* playerState) {
	// Cleanup respawn state
	(void)playerState;
}

void RespawnState::Update(PlayerState* playerState, float dt) {
	// Update respawn state
	(void)playerState;
	(void)dt;
}

void RespawnState::HandleInput(PlayerState* playerState) {
	// Handle input for respawn state
	(void)playerState;
}
#pragma endregion

#pragma region Winning
void WinningState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPWin.png");
}
void WinningState::Exit(PlayerState* playerState) {
	// Cleanup winning state
	(void)playerState;
}
void WinningState::Update(PlayerState* playerState, float dt) {
	// Update winning state
	(void)playerState;
	(void)dt;
}
void WinningState::HandleInput(PlayerState* playerState) {
	// Handle input for winning state
	(void)playerState;
}
#pragma endregion