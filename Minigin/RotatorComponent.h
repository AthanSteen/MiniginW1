#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class RotatorComponent final : public Component
	{
	public:

		explicit RotatorComponent(GameObject* ownerPtr, const glm::vec3& rotPoint, float speed);
		~RotatorComponent() override = default;

		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void SetLocalPosition(float x, float y) override;
		void SetRotationPoint(float x, float y);
		void SetRotationPoint(const glm::vec3& pos);

	private:
		Transform m_localTransform{};
		glm::vec3 m_rotationPoint;
		float m_speed;
		float m_radius;
		float m_angle;
	};
}

