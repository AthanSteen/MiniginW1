#include "Platform.h"

namespace dae
{
	Platform::Platform(GameObject* ownerPtr) : 
        Component(ownerPtr),
		m_localTransform(),
		m_width(100.0f)
    {

    }

    void Platform::Update(float /*deltaTime*/)
    {

    }

    void Platform::Render() const
    {

    }

    void Platform::SetLocalPosition(float x, float y)
    {
        m_localTransform.SetPosition(x, y, 0);
    }
}