#pragma once
#include "Component.h"
#include "Subject.h"
#include "Transform.h"
#include "TextComponent.h"

namespace dae
{
	class LivesComponent : public Component, public Subject
    {
    public:
        explicit LivesComponent(GameObject* pOwner, int lives);

        LivesComponent(const LivesComponent& other) = delete;
        LivesComponent(LivesComponent&& other) = delete;
        LivesComponent& operator=(const LivesComponent& other) = delete;
        LivesComponent& operator=(LivesComponent&& other) = delete;

        virtual void Update(float deltaTime) override { (void)deltaTime; };
        virtual void Render() const override {};

        virtual void SetLocalPosition(float x, float y) override;

        void LoseLife();
        int GetLives() const;
        bool IsDead() const;

    private:
        Transform m_localTransform{};
        int m_lives;
    };
}