#include "RotatorComponent.h"
#include "GameObject.h"

namespace dae
{
	RotatorComponent::RotatorComponent(GameObject* ownerPtr, float speed) :
		Component(ownerPtr),
		m_speed{ speed },
		m_radius{ },
		m_angle{ }
	{
		const glm::vec3 ownerWorldPos = GetOwner()->GetWorldTransform().GetPosition();
		if (GetOwner()->GetParent())
		{
			const glm::vec3 parentWorldPos = GetOwner()->GetParent()->GetWorldTransform().GetPosition();
			m_radius = glm::distance(parentWorldPos, ownerWorldPos);
		}
		else
		{
			m_radius = glm::distance(glm::vec3(0), ownerWorldPos);
		}
	}

	void RotatorComponent::Render() const
	{

	}

	void RotatorComponent::Update(float deltaTime)
	{
		if (m_radius <= 0)
			return;

		m_angle += m_speed * deltaTime;

		const glm::vec3 newPos{ m_radius * cos(m_angle), m_radius * sin(m_angle), 0.0f };

		GetOwner()->SetLocalPosition(newPos);
	}

	void RotatorComponent::SetLocalPosition(float x, float y)
	{
		m_localTransform.SetPosition(x, y, 0.0f);
	}
}