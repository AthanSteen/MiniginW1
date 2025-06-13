#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Level.h"
#include <string>
#include <memory>

namespace dae
{
    class LevelLoader : public Component
    {
    public:
        explicit LevelLoader(GameObject* ownerPtr);

        LevelLoader(const LevelLoader& other) = delete;
        LevelLoader(LevelLoader&& other) = delete;
        LevelLoader& operator=(const LevelLoader& other) = delete;
        LevelLoader& operator=(LevelLoader&& other) = delete;

        void Update(float deltaTime) override;
        void Render() const override;
		void SetLocalPosition(float, float) override {}

        void LoadLevelFromFile(const std::string& levelName, Level* outLevel);
    private:
        GameObject* m_pOwner;
    };
}