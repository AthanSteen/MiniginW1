#include "PlotComponent.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "implot.h"

#include <cmath>
#include <chrono>

namespace dae
{
    PlotComponent::PlotComponent(GameObject* ownerPtr)
        : Component(ownerPtr) 
    {

    }

    void PlotComponent::Update(float elapsedSec)
    {
        (void)elapsedSec;
    }

    void PlotComponent::Render() const
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Box 1: Trash the cache
        ImGui::Begin("Sample Control 1");

        // Numeric field
        ImGui::InputInt("##samples1", &m_numberSamples, 0, 0, ImGuiInputTextFlags_ReadOnly);

        // Decrease button
        if (ImGui::Button("-##1"))
        {
            m_numberSamples--;
        }

        // Increase button
        ImGui::SameLine();
        if (ImGui::Button("+##1"))
        {
            m_numberSamples++;
        }

        // Label
        ImGui::SameLine();
        ImGui::Text("# samples");

        // Trash the cache button
        if (ImGui::Button("Trash the cache"))
        {
            // Implement the logic for "Trash the cache"
        }

        ImGui::End();

        // Box 2: Trash the cache with GameObject3D and GameObject3DAlt
        ImGui::Begin("Sample Control 2");

        // Numeric field
        ImGui::InputInt("##samples2", &m_numberSamples, 0, 0, ImGuiInputTextFlags_ReadOnly);

        // Decrease button
        if (ImGui::Button("-##2"))
        {
            m_numberSamples--;
        }

        // Increase button
        ImGui::SameLine();
        if (ImGui::Button("+##2"))
        {
            m_numberSamples++;
        }

        // Label
        ImGui::SameLine();
        ImGui::Text("# samples");

        // Trash the cache with GameObject3D button
        if (ImGui::Button("Trash the cache with GameObject3D"))
        {
            // Implement the logic for "Trash the cache with GameObject3D"
        }

        // Trash the cache with GameObject3DAlt button
        if (ImGui::Button("Trash the cache with GameObject3DAlt"))
        {
            // Implement the logic for "Trash the cache with GameObject3DAlt"
        }

        ImGui::End();

        ImGui::Begin("Performance Graph");

        static std::vector<float> x_data, y_data_int, y_data_gameObject, y_data_gameObjectAlt;

        // Generate data if button is clicked
        if (ImGui::Button("Generate Plot Data"))
        {
            GeneratePlotData(x_data, y_data_int, y_data_gameObject, y_data_gameObjectAlt);
        }

        // Plot Data using ImPlot
        if (ImPlot::BeginPlot("Memory Performance", ImVec2(-1, 300)))
        {
            ImPlot::SetupAxes("Step Size", "Time (microseconds)", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);

            if (!x_data.empty())
            {
                ImPlot::PlotLine("Vector<int>", x_data.data(), y_data_int.data(), (int)x_data.size());
                ImPlot::PlotLine("GameObject3D", x_data.data(), y_data_gameObject.data(), (int)x_data.size());
                ImPlot::PlotLine("GameObject3DAlt", x_data.data(), y_data_gameObjectAlt.data(), (int)x_data.size());
            }

            ImPlot::EndPlot();
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void PlotComponent::SetLocalPosition(float x, float y)
    {
        m_localTransform.SetPosition(x, y, 0.0f);
    }

    void PlotComponent::GeneratePlotData(std::vector<float>& x_data,
        std::vector<float>& y_data_int,
        std::vector<float>& y_data_gameObject,
        std::vector<float>& y_data_gameObjectAlt) const
    {
        const int BUFFER_SIZE = (1 << 23);
        const int MAX_STEP = 1024;

        x_data.clear();
        y_data_int.clear();
        y_data_gameObject.clear();
        y_data_gameObjectAlt.clear();

        std::vector<int> intBuffer(BUFFER_SIZE, 1);
        std::vector<GameObject3D> gameObjectBuffer(BUFFER_SIZE);
        std::vector<GameObject3DAlt> gameObjectAltBuffer(BUFFER_SIZE);

        for (int step = 1; step <= MAX_STEP; step *= 2)
        {
            x_data.push_back(static_cast<float>(step));

            // Measure time for std::vector<int>
            y_data_int.push_back(static_cast<float>(measure_time(intBuffer, step)));

            // Measure time for GameObject3D
            y_data_gameObject.push_back(static_cast<float>(measure_time(gameObjectBuffer, step)));

            // Measure time for GameObject3DAlt
            y_data_gameObjectAlt.push_back(static_cast<float>(measure_time(gameObjectAltBuffer, step)));
        }
    }

    template <typename T>
    double PlotComponent::measure_time(std::vector<T>& buffer, int step) const
    {
        const auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < buffer.size(); i += step) {
            buffer[i].ID *= 2;
        }
        const auto end = std::chrono::high_resolution_clock::now();

        return static_cast<double>(
            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
    }
    
    double PlotComponent::measure_time(std::vector<int>& buffer, int step) const
    {
        const auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < buffer.size(); i += step) {
            buffer[i] *= 2;
        }
        const auto end = std::chrono::high_resolution_clock::now();

        return static_cast<double>(
            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
    }
}