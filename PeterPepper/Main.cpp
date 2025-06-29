#pragma once
#include <SDL.h>

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "Scene.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "StopMoveCommand.h"
#include "LivesComponent.h"
#include "LivesDisplayObserver.h"
#include "KillCommand.h"
#include "ScoreComponent.h"
#include "ScoreDisplayObserver.h"
#include "AddScoreCommand.h"
#include <Xinput.h>
#include "SDLMixerSoundService.h"
#include "ServiceLocator.h"
#include "Level.h"
#include "LevelLoader.h"
#include "MuteCommands.h"
#include <iostream>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	dae::ServiceLocator::RegisterSoundService(std::make_unique<dae::SDLMixerSoundService>());

	dae::ServiceLocator::GetSoundService()->PlaySound("Sound/BGM.wav", true);

	dae::Renderer::GetInstance().SetZoom(2.5f);

	auto gameObject = std::make_unique<dae::GameObject>();
	gameObject->AddComponent<dae::TextureComponent>("background.tga");
	scene.Add(std::move(gameObject));

	/*auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	gameObject = std::make_unique<dae::GameObject>();
	gameObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	gameObject->SetLocalPosition(80, 20);
	scene.Add(std::move(gameObject));*/

	auto objLevelLoader = std::make_unique<dae::GameObject>();
	auto levelLoader = objLevelLoader->AddComponent<dae::LevelLoader>();
	auto level = objLevelLoader->AddComponent<dae::Level>();
	levelLoader->LoadLevelFromFile("level1.json", level);
	scene.Add(std::move(objLevelLoader));
		
	auto char1 = std::make_unique<dae::GameObject>();
	const float CHAR1_SPEED{ 1.f };
	auto player = char1->AddComponent<PlayerComponent>();
	player->SetLevel(level);
	auto playerSpawn = level->GetPlayerSpawn();
	char1->SetLocalPosition(glm::vec3(playerSpawn.x, playerSpawn.y, 0.f));

#pragma region InputBindingsKeyboard
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_w, InputState::Pressed, std::make_unique<dae::MoveCommand>(char1.get(), CHAR1_SPEED, glm::vec2(0, -1)));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_s, InputState::Pressed, std::make_unique<dae::MoveCommand>(char1.get(), CHAR1_SPEED, glm::vec2(0, 1)));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_a, InputState::Pressed, std::make_unique<dae::MoveCommand>(char1.get(), CHAR1_SPEED, glm::vec2(-1, 0)));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_d, InputState::Pressed, std::make_unique<dae::MoveCommand>(char1.get(), CHAR1_SPEED, glm::vec2(1, 0)));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_w, InputState::Up, std::make_unique<dae::StopMoveCommand>(char1.get(), glm::vec2(0,-1)));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_a, InputState::Up, std::make_unique<dae::StopMoveCommand>(char1.get(), glm::vec2(0,1)));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_s, InputState::Up, std::make_unique<dae::StopMoveCommand>(char1.get(), glm::vec2(-1,0)));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_d, InputState::Up, std::make_unique<dae::StopMoveCommand>(char1.get(), glm::vec2(1,0)));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_c, InputState::Down, std::make_unique<dae::KillCommand>(char1.get()));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_z, InputState::Down, std::make_unique<dae::AddScoreCommand>(char1.get(), 10));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_x, InputState::Down, std::make_unique<dae::AddScoreCommand>(char1.get(), 100));

	std::cout << "F2|: Mute Game" << std::endl;
	std::cout << "F3|: Unmute Game" << std::endl;

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_F2, InputState::Down, std::make_unique<dae::MuteCommand>());
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_F3, InputState::Down, std::make_unique<dae::UnmuteCommand>());
#pragma endregion

#pragma region InputBindingsController
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_UP, InputState::Pressed, std::make_unique<dae::MoveCommand>(char1.get(), CHAR1_SPEED, glm::vec2(0, -1)));
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_DOWN, InputState::Pressed, std::make_unique<dae::MoveCommand>(char1.get(), CHAR1_SPEED, glm::vec2(0, 1)));
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, InputState::Pressed, std::make_unique<dae::MoveCommand>(char1.get(), CHAR1_SPEED, glm::vec2(-1, 0)));
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, InputState::Pressed, std::make_unique<dae::MoveCommand>(char1.get(), CHAR1_SPEED, glm::vec2(1, 0)));
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_UP, InputState::Up, std::make_unique<dae::StopMoveCommand>(char1.get(), glm::vec2(0,-1)));
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_DOWN, InputState::Up, std::make_unique<dae::StopMoveCommand>(char1.get(), glm::vec2(0,1)));
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, InputState::Up, std::make_unique<dae::StopMoveCommand>(char1.get(), glm::vec2(-1,0)));
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, InputState::Up, std::make_unique<dae::StopMoveCommand>(char1.get(), glm::vec2(1,0)));
#pragma endregion
	scene.Add(std::move(char1));

	auto scoreObject = std::make_unique<dae::GameObject>();
	
	auto hiScoreLabel = scoreObject->AddComponent<dae::TextComponent>("SCORE", dae::ResourceManager::GetInstance().LoadFont("Burger.otf", 8));
	hiScoreLabel->SetColor({ 255, 0, 0, 255 });
	hiScoreLabel->SetLocalPosition(2, 2);

	auto scoreComponent = scoreObject->AddComponent<dae::ScoreComponent>();
	level->SetScoreComponent(scoreComponent);

	auto scoreDisplay = scoreObject->AddComponent<dae::TextComponent>("0", dae::ResourceManager::GetInstance().LoadFont("Burger.otf", 8));
	scoreDisplay->SetColor();
	scoreDisplay->SetLocalPosition(10, 11);
	
	auto scoreDisplayObserver = scoreObject->AddComponent<dae::ScoreDisplayObserver>(scoreDisplay);
	scoreComponent->AddObserver(scoreDisplayObserver);

	scene.Add(std::move(scoreObject));

	//TODO: z level to Render so player always on top of burger pieces
}

void find_resources()
{
	constexpr int MAX_TRAVERSAL{ 3 };

	const std::filesystem::path resFolderName{ "Data" };
	int counter{ 0 };

	while (!std::filesystem::exists(resFolderName) && counter < MAX_TRAVERSAL)
	{
		std::filesystem::current_path("..");
		counter++;
	}

	std::filesystem::current_path(resFolderName);
}

int main(int, char*[]) {
	find_resources();
	dae::Minigin engine{};
	engine.Run(load);
    return 0;
}