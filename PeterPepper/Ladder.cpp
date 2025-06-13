#include "Ladder.h"

namespace dae
{
    Ladder::Ladder(GameObject* ownerPtr) : 
        Component(ownerPtr),
        m_localTransform(),
		m_height(100.0f),
		m_width(20.0f)
    {

    }

    void Ladder::Update(float /*deltaTime*/)
    {

    }

    void Ladder::Render() const
    {

    }

    void Ladder::SetLocalPosition(float x, float y)
    {
        m_localTransform.SetPosition(x, y, 0);
    }
}