#include "Windows.h"
#include "XInputImpl.h"

namespace dae {
	bool XInputImpl::ProcessControllerInput(std::unordered_map<WORD, std::unordered_map<InputState, std::unique_ptr<Command>>>& controllerCommands) {
		XINPUT_STATE controllerState;
		for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
			ZeroMemory(&controllerState, sizeof(XINPUT_STATE));
			if (XInputGetState(i, &controllerState) == ERROR_SUCCESS) {
				// Controller is connected
				for (const auto& [button, commands] : controllerCommands) {
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
}