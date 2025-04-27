#include "AddScoreCommand.h"
#include "ScoreComponent.h"

namespace dae
{
	AddScoreCommand::AddScoreCommand(GameObject* pObject, int score) 
        : m_pObject(pObject), m_score(score)
    {
    }

    void AddScoreCommand::Execute()
    {
        if (m_pObject) {
            if (auto score = m_pObject->GetComponent<ScoreComponent>()) {
				score->AddScore(m_score);
            }
        }
    }
}