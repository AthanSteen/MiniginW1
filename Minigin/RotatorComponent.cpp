#include "RotatorComponent.h"
#include "GameObject.h"

namespace dae
{
	RotatorComponent::RotatorComponent(GameObject* ownerPtr, const glm::vec3& rotPoint, float speed) :
		Component(ownerPtr),
		m_rotationPoint{ rotPoint },
		m_speed{ speed },
		m_radius{ },
		m_angle{ }
	{
		if (GetOwner()->GetParent() == nullptr)
		{
			const glm::vec3 ownerWorldPos = GetOwner()->GetWorldTransform().GetPosition();
			m_radius = glm::distance(m_rotationPoint, ownerWorldPos);
		}
		else
		{
			const glm::vec3 ownerWorldPos = GetOwner()->GetWorldTransform().GetPosition();
			const glm::vec3 parentWorldPos = GetOwner()->GetParent()->GetWorldTransform().GetPosition();
			m_radius = glm::distance(parentWorldPos + m_rotationPoint, ownerWorldPos);
		}
	}

	void RotatorComponent::Render() const
	{

	}

	void RotatorComponent::Update(float deltaTime)
	{
		m_angle += m_speed * deltaTime;

		const glm::vec3 newPos{ m_rotationPoint.x + m_radius * cos(m_angle), m_rotationPoint.y + m_radius * sin(m_angle), 0.0f };

		GetOwner()->SetLocalPosition(newPos);
	}

	void RotatorComponent::SetLocalPosition(float x, float y)
	{
		m_localTransform.SetPosition(x, y, 0.0f);
	}

	void RotatorComponent::SetRotationPoint(float x, float y)
	{
		SetRotationPoint(glm::vec3(x, y, 0.0f));
	}

	void RotatorComponent::SetRotationPoint(const glm::vec3& pos)
	{
		m_rotationPoint = pos;
	}
}