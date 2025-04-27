#pragma once
#include "Component.h"
#include "Subject.h"
#include "Transform.h"
#include "TextComponent.h"

namespace dae
{
    class ScoreComponent : public Component, public Subject
    {
    public:
        explicit ScoreComponent(GameObject* pOwner);

        ScoreComponent(const ScoreComponent& other) = delete;
        ScoreComponent(ScoreComponent&& other) = delete;
        ScoreComponent& operator=(const ScoreComponent& other) = delete;
        ScoreComponent& operator=(ScoreComponent&& other) = delete;

        virtual void Update(float deltaTime) override { (void)deltaTime; };
        virtual void Render() const override {};

        virtual void SetLocalPosition(float x, float y) override;

        void AddScore(int score);
        int GetScore() const;
    private:
        Transform m_localTransform{};
        int m_score;
    };
}