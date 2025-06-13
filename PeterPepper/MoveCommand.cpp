#include "MoveCommand.h"
#include "PlayerComponent.h"

namespace dae
{
    MoveCommand::MoveCommand(GameObject* pObject, float speed, const glm::vec2& direction)
        : m_pObject(pObject)
        , m_speed(speed)
        , m_direction(direction)
    {
    }

    void MoveCommand::Execute()
    {
        if (m_pObject)
        {
            glm::vec3 pos{ m_pObject->GetWorldTransform().GetPosition() };
            glm::vec3 offset(m_direction, 0.f);
            m_pObject->SetLocalPosition( pos + offset * m_speed);

            auto* playerComp = m_pObject->GetComponent<PlayerComponent>();
            if (playerComp)
            {
                playerComp->SetDirection(m_direction);
            }
        }
    }
}