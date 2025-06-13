#pragma once
#include "GameObject.h"
#include "Component.h"
#include <vector>
#include <memory>
#include "BurgerPiece.h"
#include "Platform.h"
#include "Ladder.h"
#include <glm.hpp>

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
        void SetLocalPosition(float, float) override {}

		void SetPlayerSpawn(const glm::vec2& spawn) { m_playerSpawn = spawn; }

        void AddPlatform(std::unique_ptr<Platform> platform);
        void AddLadder(std::unique_ptr<Ladder> ladder);
        void AddBurgerPiece(std::unique_ptr<BurgerPiece> piece);

        const std::vector<std::unique_ptr<Platform>>& GetPlatforms() const        { return m_platforms; }
        const std::vector<std::unique_ptr<Ladder>>& GetLadders() const          { return m_ladders; }
		const std::vector<std::unique_ptr<BurgerPiece>>& GetBurgerPieces() const    { return m_burgerPieces; }

    private:
        std::vector<std::unique_ptr<Platform>> m_platforms;
        std::vector<std::unique_ptr<Ladder>> m_ladders;
        std::vector<std::unique_ptr<BurgerPiece>> m_burgerPieces;

        glm::vec2 m_playerSpawn;
    };
}