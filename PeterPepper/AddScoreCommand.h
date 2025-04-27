#pragma once
#include "Command.h"
#include "GameObject.h"

namespace dae
{
    class AddScoreCommand final : public Command
    {
    public:
        AddScoreCommand(GameObject* pObject, int score);
        ~AddScoreCommand() override = default;

        AddScoreCommand(const AddScoreCommand&) = delete;
        AddScoreCommand& operator=(const AddScoreCommand&) = delete;
        AddScoreCommand(AddScoreCommand&&) = delete;
        AddScoreCommand& operator=(AddScoreCommand&&) = delete;

        void Execute() override;

    private:
        GameObject* m_pObject;
		int m_score;
    };
}