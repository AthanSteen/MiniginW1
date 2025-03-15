#include <SDL.h>
#include "InputManager.h"
#include "backends/imgui_impl_sdl2.h"
#include "Xinput.h"

namespace dae{
	class XInputImpl {
	public:
		XInputImpl() = default;

		bool ProcessInput() {
			XINPUT_STATE controllerState;
			for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
				ZeroMemory(&controllerState, sizeof(XINPUT_STATE));
				if (XInputGetState(i, &controllerState) == ERROR_SUCCESS) {
					// Controller is connected
					for (const auto& [button, commands] : m_ControllerCommands) {
						bool isPressed = (controllerState.Gamepad.wButtons & button) != 0;
						bool wasPressed = (m_previousState.Gamepad.wButtons & button) != 0;

						for (const auto& [commandState, command] : commands) {
							if ((commandState == InputState::Down && isPressed && !wasPressed) ||
								(commandState == InputState::Up && !isPressed && wasPressed) ||
								(commandState == InputState::Pressed && isPressed && wasPressed)) {
								command->Execute();
							}
						}
					}
					m_previousState = controllerState;
				}
			}
			return true;
		}

		void BindControllerCommand(WORD button, InputState state, Command* command) {
			m_ControllerCommands[button][state] = std::unique_ptr<Command>(command);
		}

	private:
		std::unordered_map<WORD, std::unordered_map<InputState, std::unique_ptr<Command>>> m_ControllerCommands;
		XINPUT_STATE m_previousState{};
	};


	InputManager::InputManager() : m_XInputImpl(std::make_unique<XInputImpl>()) {}
	InputManager::~InputManager() = default;

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
		m_XInputImpl->ProcessInput();
		return true;
	}

	void InputManager::BindKeyboardCommand(int key, InputState state, Command* command)
	{
		m_KeyboardCommands[key][state] = std::unique_ptr<Command>(command);
	}

	void InputManager::BindControllerCommand(WORD button, InputState state, Command* command)
	{
		m_XInputImpl.get()->BindControllerCommand(button, state, command);
	}
}