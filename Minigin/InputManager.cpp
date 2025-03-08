#include <SDL.h>
#include <SDL_syswm.h>
#include "Windows.h"
#include "InputManager.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

namespace dae{
	bool InputManager::ProcessInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}

			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
				const auto KEY = e.key.keysym.sym;
				const auto STATE = (e.type == SDL_KEYDOWN) ? InputState::Pressed : InputState::Up;
				if (m_KeyboardCommands.find(KEY) != m_KeyboardCommands.end() &&
					m_KeyboardCommands[KEY].find(STATE) != m_KeyboardCommands[KEY].end()) {
					m_KeyboardCommands[KEY][STATE]->Execute();
				}
			}

			//process event for IMGUI
			ImGui_ImplSDL2_ProcessEvent(&e);
		}

		XINPUT_STATE controllerState;
		for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
			ZeroMemory(&controllerState, sizeof(XINPUT_STATE));
			if (XInputGetState(i, &controllerState) == ERROR_SUCCESS) {
				// Controller is connected
				for (const auto& [button, commands] : m_ControllerCommands)
				{
					bool isPressed = (controllerState.Gamepad.wButtons & button) != 0;
					bool wasPressed = (controllerState.Gamepad.wButtons & button) != 0;

					for (const auto& [commandState, command] : commands)
					{
						if ((commandState == InputState::Down && isPressed) ||
							(commandState == InputState::Up && !isPressed && wasPressed) ||
							(commandState == InputState::Pressed && isPressed && wasPressed))
						{
							command->Execute();
						}
					}
				}
				m_PreviousState = controllerState;
			}
		}

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