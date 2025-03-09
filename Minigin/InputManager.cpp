#include <SDL.h>
#include "InputManager.h"
#include "backends/imgui_impl_sdl2.h"

namespace dae{
	InputManager::InputManager() : m_XInputImpl(std::make_unique<XInputImpl>()) {}

	bool InputManager::ProcessInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}

			//process event for IMGUI
			ImGui_ImplSDL2_ProcessEvent(&e);
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);
		for (auto& [key, commands] : m_KeyboardCommands) {
			bool isPressed = state[SDL_GetScancodeFromKey(key)];
			for (auto& [commandState, command] : commands) {
				if ((commandState == InputState::Pressed && isPressed) ||
					(commandState == InputState::Up && !isPressed) ||
					(commandState == InputState::Down && isPressed)) {
					command->Execute();
				}
			}
		}
		m_XInputImpl->ProcessControllerInput(m_ControllerCommands);

		return true;
	}

	void InputManager::BindKeyboardCommand(int key, InputState state, Command* command)
	{
		m_KeyboardCommands[key][state] = std::unique_ptr<Command>(command);
	}

	void InputManager::BindControllerCommand(WORD button, InputState state, Command* command)
	{
		m_ControllerCommands[button][state] = std::unique_ptr<Command>(command);
	}
}