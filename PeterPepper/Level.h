#pragma once
#include "Component.h"

namespace dae
{
    class Level : public Component
    {
    public:
        explicit Level(GameObject* ownerPtr);

        Level(const Level& other) = delete;
        Level(Level&& other) = delete;
        Level& operator=(const Level& other) = delete;
        Level& operator=(Level&& other) = delete;

        void Update(float deltaTime) override;
        void Render() const override;

    private:
    };
}