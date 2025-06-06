#include "PlayerState.h"

PlayerState::PlayerState(dae::SpriteSheetComponent* spriteSheet) 
	: m_StateMachine(std::make_unique<StateMachine<PlayerState>>()),
	m_pTexture(spriteSheet)
{
	m_StateMachine->ChangeState(std::make_unique<IdleState>());
}

void PlayerState::Update(float dt) {
    m_StateMachine->Update(this, dt);
}

void PlayerState::HandleInput() {
    m_StateMachine->HandleInput(this);
}

void PlayerState::ChangeState(std::unique_ptr<State<PlayerState>> newState) {
    m_StateMachine->ChangeState(std::move(newState));
}


#pragma region Idle

void IdleState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPIdle.png");
}

void IdleState::Exit(PlayerState*) {
	// Cleanup idle state
}

void IdleState::Update(PlayerState*, float) {
	// Update idle state
}

void IdleState::HandleInput(PlayerState*) {
	// Handle input for idle state
}
#pragma endregion

#pragma region Walking
void WalkingState::Enter(PlayerState* playerState) {
	//TODO switch logic for direction
	playerState->GetSpriteSheet()->SetSpriteSheet("PPLeft.png");
}

void WalkingState::Exit(PlayerState*) {
	// Cleanup walking state
}

void WalkingState::Update(PlayerState*, float) {
	// Update walking state
}

void WalkingState::HandleInput(PlayerState*) {
	// Handle input for walking state
}
#pragma endregion

#pragma region Climbing
void ClimbingState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPUp.png");
}

void ClimbingState::Exit(PlayerState*) {
	// Cleanup climbing state
}

void ClimbingState::Update(PlayerState*, float) {
	// Update climbing state
}

void ClimbingState::HandleInput(PlayerState*) {
	// Handle input for climbing state
}
#pragma endregion

#pragma region Spray
void SprayState::Enter(PlayerState*) {
	// Initialize spray state
}

void SprayState::Exit(PlayerState*) {
	// Cleanup spray state
}

void SprayState::Update(PlayerState*, float) {
	// Update spray state
}

void SprayState::HandleInput(PlayerState*) {
	// Handle input for spray state
}
#pragma endregion

#pragma region Hit
void HitState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPHit.png");
}

void HitState::Exit(PlayerState*) {
	// Cleanup hit state
}

void HitState::Update(PlayerState*, float) {
	// Update hit state
}

void HitState::HandleInput(PlayerState*) {
	// Handle input for hit state
}
#pragma endregion

#pragma region Dead
void DeadState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPDead.png");
}

void DeadState::Exit(PlayerState*) {
	// Cleanup hit state
}

void DeadState::Update(PlayerState*, float) {
	// Update hit state
}

void DeadState::HandleInput(PlayerState*) {
	// Handle input for hit state
}
#pragma endregion

#pragma region Respawn
void RespawnState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPIdle.png");
}

void RespawnState::Exit(PlayerState*) {
	// Cleanup respawn state
}

void RespawnState::Update(PlayerState*, float) {
	// Update respawn state
}

void RespawnState::HandleInput(PlayerState*) {
	// Handle input for respawn state
}
#pragma endregion

#pragma region Winning
void WinningState::Enter(PlayerState* playerState) {
	playerState->GetSpriteSheet()->SetSpriteSheet("PPWin.png");
}
void WinningState::Exit(PlayerState*) {
	// Cleanup winning state
}
void WinningState::Update(PlayerState*, float) {
	// Update winning state
}
void WinningState::HandleInput(PlayerState*) {
	// Handle input for winning state
}
#pragma endregion