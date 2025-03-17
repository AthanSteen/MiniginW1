#include "KillCommand.h"
#include "LivesComponent.h"

namespace dae
{
    KillCommand::KillCommand(GameObject* pObject) : m_pObject(pObject)
    {
    }

    void KillCommand::Execute()
    {
        if (m_pObject) {
            if (auto health = m_pObject->GetComponent<LivesComponent>()) {
                health->LoseLife();
            }
        }
    }
}