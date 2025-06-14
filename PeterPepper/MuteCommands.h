#pragma once
#include "Command.h"
#include "ServiceLocator.h"

namespace dae
{
    class MuteCommand final : public Command
    {
    public:
        void Execute() override
        {
            ServiceLocator::GetSoundService()->MuteAll();
        }
    };

    class UnmuteCommand final : public Command
    {
    public:
        void Execute() override
        {
            ServiceLocator::GetSoundService()->UnmuteAll();
        }
    };
}