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

            auto* playerComp = m_pObject->GetComponent<PlayerComponent>();
            if (playerComp)
            {
                auto currentDirection = playerComp->GetDirection();

				playerComp->Move(offset.x * m_speed, offset.y * m_speed); 
                
                if (m_direction.x != 0.f)
                {
                    if (currentDirection.x == m_direction.x * -1)
                        currentDirection.x = 0.f;
                    else if (currentDirection.x != m_direction.x)
                        currentDirection.x = m_direction.x;
                }
                else
                {
                    if (currentDirection.y == m_direction.y * -1)
                        currentDirection.y = 0.f;
                    else if (currentDirection.y != m_direction.y)
                        currentDirection.y = m_direction.y;
                }
                //trying to fix correct image but now working
                playerComp->SetDirection(currentDirection);
            }
            else
                m_pObject->SetLocalPosition(pos + offset * m_speed);
        }
    }
}