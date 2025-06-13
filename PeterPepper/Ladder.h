#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class Ladder : public Component
    {
    public:
        explicit Ladder(GameObject* ownerPtr);

        Ladder(const Ladder& other) = delete;
        Ladder(Ladder&& other) = delete;
        Ladder& operator=(const Ladder& other) = delete;
        Ladder& operator=(Ladder&& other) = delete;

        void Update(float deltaTime) override;
        void Render() const override;

        void SetLocalPosition(float x, float y) override;

        void SetHeight(float height) { m_height = height; }
        void SetWidth(float width) { m_width = width; }

    private:
        Transform m_localTransform;
        float m_height;
        float m_width;
    };
}