#include "ScoreComponent.h"

namespace dae
{
    ScoreComponent::ScoreComponent(GameObject* pOwner)
        : Component(pOwner), m_score(0) {}

    void ScoreComponent::AddScore(int score)
    {
		m_score += score;
        NotifyObservers(Event::ScoreChanged, this);
    }

    int ScoreComponent::GetScore() const
    {
        return m_score;
    }

    void ScoreComponent::SetLocalPosition(float x, float y)
    {
        m_localTransform.SetPosition(x, y, 0.0f);
    }
}