#pragma once
#include "Windows.h"
#include "Singleton.h"
#include "Command.h"
#include "InputState.h"
#include "XInputImpl.h"
#include <unordered_map>
#include <memory>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		bool ProcessInput();
		void BindKeyboardCommand(int key, InputState state, Command* command);
		void BindControllerCommand(WORD button, InputState state, Command* command);
    private:
        std::unordered_map<int, std::unordered_map<InputState, std::unique_ptr<Command>>> m_KeyboardCommands;
        std::unordered_map<WORD, std::unordered_map<InputState, std::unique_ptr<Command>>> m_ControllerCommands;
		std::unique_ptr<class XInputImpl> m_XInputImpl;
	};
}
