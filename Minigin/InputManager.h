#pragma once
#include "Windows.h"
#include "Singleton.h"
#include "Command.h"
#include "InputState.h"
#include <unordered_map>
#include <memory>

namespace dae
{
	class XInputImpl;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		bool ProcessInput();
		void BindKeyboardCommand(int key, InputState state, Command* command);
		void BindControllerCommand(WORD button, InputState state, Command* command);
    private:
		Uint8* m_previousState;
        std::unordered_map<int, std::unordered_map<InputState, std::unique_ptr<Command>>> m_KeyboardCommands;
		std::unique_ptr<XInputImpl> m_XInputImpl;
	};
}
