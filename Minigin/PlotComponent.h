#pragma once

#include "Component.h"

namespace dae
{
    class PlotComponent final : public Component
    {
    public:
        explicit PlotComponent(GameObject* ownerPtr);

        PlotComponent(const PlotComponent& other) = delete;
        PlotComponent(PlotComponent&& other) = delete;
        PlotComponent& operator=(const PlotComponent& other) = delete;
        PlotComponent& operator=(PlotComponent&& other) = delete;

        void Update(float deltaTime) override;
        void Render() const override;
    };
}
