#pragma once
#include "Command.h"
#include "GameObject.h"

namespace dae
{
    class KillCommand final : public Command
    {
    public:
        KillCommand(GameObject* pObject);
        ~KillCommand() override = default;

        KillCommand(const KillCommand&) = delete;
        KillCommand& operator=(const KillCommand&) = delete;
        KillCommand(KillCommand&&) = delete;
        KillCommand& operator=(KillCommand&&) = delete;

        void Execute() override;

    private:
        GameObject* m_pObject;
    };
}