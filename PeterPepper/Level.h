#pragma once
#include "GameObject.h"
#include "Component.h"
#include <vector>
#include <memory>
#include "BurgerPiece.h"
#include "Platform.h"
#include "Ladder.h"
#include <glm.hpp>
#include "ScoreComponent.h"

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
		const glm::vec2& GetPlayerSpawn() const { return m_playerSpawn; }

        void AddPlatform(std::unique_ptr<Platform> platform);
        void AddLadder(std::unique_ptr<Ladder> ladder);
        void AddBurgerPiece(std::unique_ptr<BurgerPiece> piece);
        
        bool isOverlappingPlatform(const glm::vec2& playerPos, const glm::vec2& playerSize) const;
        bool isOverlappingLadders(const glm::vec2& playerPos, const glm::vec2& playerSize) const;

        std::vector<Platform*> GetPlatforms()
        {
            std::vector<Platform*> platforms;
            platforms.reserve(m_platforms.size());
            for (auto& platform : m_platforms)
            {
                platforms.push_back(platform.get());
            }
            return platforms;
        }

        std::vector<Ladder*> GetLadders()
        {
            std::vector<Ladder*> ladders;
            ladders.reserve(m_ladders.size());
            for (auto& ladder : m_ladders)
            {
                ladders.push_back(ladder.get());
            }
            return ladders;
        }

        std::vector<BurgerPiece*> GetBurgerPieces()
        {
            std::vector<BurgerPiece*> pieces;
            pieces.reserve(m_burgerPieces.size());
            for (auto& piece : m_burgerPieces)
            {
                pieces.push_back(piece.get());
            }
            return pieces;
        }

        void SetScoreComponent(ScoreComponent* pScore) { m_pScoreComponent = pScore; }
        ScoreComponent* GetScoreComponent() const { return m_pScoreComponent; }
    private:
        std::vector<std::unique_ptr<Platform>> m_platforms;
        std::vector<std::unique_ptr<Ladder>> m_ladders;
        std::vector<std::unique_ptr<BurgerPiece>> m_burgerPieces;

        glm::vec2 m_playerSpawn;

        ScoreComponent* m_pScoreComponent{ nullptr };
    };
}