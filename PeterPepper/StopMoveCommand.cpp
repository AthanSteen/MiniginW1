#include "StopMoveCommand.h"
#include "PlayerComponent.h"

namespace dae
{
    StopMoveCommand::StopMoveCommand(GameObject* pObject, const glm::vec2& direction)
        : m_pObject(pObject)
        , m_direction(direction)
    {
    }

    void StopMoveCommand::Execute()
    {
        if (m_pObject)
        {
            auto* playerComp = m_pObject->GetComponent<PlayerComponent>();
            if (playerComp)
            {
                playerComp->SetDirection(glm::vec2(0,0));
            }
        }
    }
}