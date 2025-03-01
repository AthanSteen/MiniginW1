#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class RotatorComponent final : public Component
	{
	public:

		explicit RotatorComponent(GameObject* ownerPtr, float speed);
		~RotatorComponent() override = default;

		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void SetLocalPosition(float x, float y) override;

	private:
		Transform m_localTransform{};
		float m_speed;
		float m_radius;
		float m_angle;
	};
}

