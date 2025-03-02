#pragma once

#include "Component.h"
#include "Transform.h"
#include "vector"

namespace dae
{
    enum class CacheType
    {
        CacheInt,
        CacheGameObject3D,
        CacheGameObject3DAlt
    };

    struct TestTransform
    {
        float matrix[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    };

    class GameObject3D
    {
    public:
        TestTransform transform{};
        int ID{ 1 };
    };

    class GameObject3DAlt
    {
    public:
        int ID{ 1 };
        TestTransform* transform{ nullptr };
    };

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
        void SetLocalPosition(float x, float y) override;
    private:
        Transform m_localTransform{};
        mutable int m_numberSamples{100};

        void GeneratePlotData(std::vector<float>& x_data,
            std::vector<float>& y_data_int,
            std::vector<float>& y_data_gameObject,
            std::vector<float>& y_data_gameObjectAlt) const;

        template <typename T>
        double measure_time(std::vector<T>& buffer, int step) const;
        double measure_time(std::vector<int>& buffer, int step) const;
    };
}
