#include "MoveCommand.h"

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
        }
    }
}