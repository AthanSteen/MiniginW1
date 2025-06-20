#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "chrono"
#include "thread"

#include <iostream>

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 BurgerTime - Van den Steen Athan 2GD10E",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		664,
		684,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init();
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	bool doContinue = true;
    auto lastTime = std::chrono::high_resolution_clock::now(); 
	float lag = 0.0f;

	//make a config.h for these values?
	constexpr float fixedTimeStep = 0.016f; // 16ms per frame (~60 FPS)
	constexpr int msPerFrame = 16;          // Target frame duration in milliseconds
	
	while (doContinue)
	{
		const auto currentTime = std::chrono::steady_clock().now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count(); 
		lastTime = currentTime;
		lag += deltaTime;

		doContinue = input.ProcessInput();

		while (lag >= fixedTimeStep)
		{
			sceneManager.Update(fixedTimeStep);
			lag -= fixedTimeStep;
		}
		sceneManager.Update(deltaTime);
		renderer.Render();

		const auto sleepTime = currentTime + std::chrono::milliseconds(msPerFrame) - std::chrono::steady_clock().now();
		
		//std::cout << sleepTime << std::endl; 

		if (sleepTime > std::chrono::milliseconds(0)) // Ensure we don't sleep for negative time
		{
			std::this_thread::sleep_for(sleepTime);
		}
	}
}
