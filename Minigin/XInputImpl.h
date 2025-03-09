#pragma once
#include "Xinput.h"
#include "Command.h"
#include "InputState.h"
#include <unordered_map>
#include <memory>

namespace dae {
	class XInputImpl {
	public:
		bool ProcessControllerInput(std::unordered_map<WORD, std::unordered_map<InputState, std::unique_ptr<Command>>>& controllerCommands);
	private:
		XINPUT_STATE m_previousState{};
	};
}