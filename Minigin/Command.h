#pragma once
#include "ServiceLocator.h"
class Command {
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};