#pragma once
#include "Command.h"
#include "GameObject.h"
#include <glm.hpp>

namespace dae
{
    class StopMoveCommand final : public Command
    {
    public:
        StopMoveCommand(GameObject* pObject, const glm::vec2& direction);
        virtual ~StopMoveCommand() = default;
        virtual void Execute() override;

    private:
        GameObject* m_pObject;
        glm::vec2 m_direction;
    };
}