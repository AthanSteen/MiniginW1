#include "LivesComponent.h"

namespace dae 
{
    LivesComponent::LivesComponent(GameObject* pOwner, int lives)
        : Component(pOwner), m_lives(lives) {}

    void LivesComponent::LoseLife()
    {
        if (m_lives > 0)
        {
            --m_lives;
			NotifyObservers(Event::PlayerDied,this);
        }
    }

    int LivesComponent::GetLives() const
    {
        return m_lives;
    }

    bool LivesComponent::IsDead() const
    {
        return m_lives <= 0;
    }

    void LivesComponent::SetLocalPosition(float x, float y)
    {
        m_localTransform.SetPosition(x, y, 0.0f);
    }
}