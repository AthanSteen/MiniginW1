#pragma once
#include "LevelLoader.h"
#include "fstream"
#include "BurgerPiece.h"
#include "Ladder.h"
#include "Platform.h"
#include <glm.hpp>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

namespace dae
{
    LevelLoader::LevelLoader(GameObject* ownerPtr)
		: Component(ownerPtr), 
        m_pOwner(ownerPtr)
    {

    }

    void LevelLoader::Update(float /*deltaTime*/)
    {

    }

    void LevelLoader::Render() const
    {

    }

    void LevelLoader::LoadLevelFromFile(const std::string& levelName, Level* outLevel)
	{
        try
        {
            std::ifstream file(levelName);
            if (!file.is_open())
            {
                std::cerr << "Error: Could not open level file: " << levelName << std::endl;
            }

            json data;
            file >> data;

            // --- Player Spawn ---
            if (data.contains("playerSpawn") && data["playerSpawn"].is_object())
            {
                const auto& spawn = data["playerSpawn"];
                if (spawn.contains("x") && spawn["x"].is_number() &&
                    spawn.contains("y") && spawn["y"].is_number())
                {
                    outLevel->SetPlayerSpawn(glm::vec2(spawn["x"].get<float>(), spawn["y"].get<float>()));
                }
                else
                {
                    std::cerr << "Warning: 'playerSpawn' data (x, y missing or not numbers) in " << levelName << std::endl;
                }
            }
            else
            {
                std::cerr << "Warning: 'playerSpawn' not found " << levelName << std::endl;
            }

            if (data.contains("enemySpawns") && data["enemySpawns"].is_array())
            {
                for (const auto& enemySpawn : data["enemySpawns"])
                {
                    if (enemySpawn.is_object() && enemySpawn.contains("x") && enemySpawn["x"].is_number() &&
                        enemySpawn.contains("y") && enemySpawn["y"].is_number())
                    {
                        // level->AddEnemySpawn(glm::vec2(enemySpawn["x"].get<float>(), enemySpawn["y"].get<float>()));
                        std::cout << "Enemy spawn found at: (" << enemySpawn["x"].get<float>() << ", " << enemySpawn["y"].get<float>() << ")\n";
                    }
                    else
                    {
                        std::cerr << "Warning: enemySpawn entry in " << levelName << std::endl;
                    }
                }
            }
            else
            {
                std::cerr << "Warning: 'enemySpawns' not found" << levelName << std::endl;
            }

            if (data.contains("platforms") && data["platforms"].is_array())
            {
                for (const auto& p : data["platforms"])
                {
                    if (p.is_object() && p.contains("startX") && p["startX"].is_number() &&
                        p.contains("endX") && p["endX"].is_number() &&
                        p.contains("y") && p["y"].is_number())
                    {
                        float startX = p["startX"].get<float>();
                        float endX = p["endX"].get<float>();
                        float y = p["y"].get<float>();
                        float width = endX - startX;

                        auto platform = std::make_unique<Platform>(m_pOwner);
						platform->SetLocalPosition(startX, y);
						platform->SetWidth(width);

                        outLevel->AddPlatform(std::move(platform));
                    }
                    else
                    {
                        std::cerr << "Warning: platform entry (startX, endX, y missing or not numbers) in " << levelName << std::endl;
                    }
                }
            }
            else
            {
                std::cerr << "Warning: 'platforms' not found " << levelName << std::endl;
            }

            if (data.contains("ladders") && data["ladders"].is_array())
            {
                for (const auto& l : data["ladders"])
                {
                    if (l.is_object() && l.contains("x") && l["x"].is_number() &&
                        l.contains("topY") && l["topY"].is_number() &&
                        l.contains("bottomY") && l["bottomY"].is_number())
                    {
                        float x = l["x"].get<float>();
                        float topY = l["topY"].get<float>();
                        float bottomY = l["bottomY"].get<float>();
                        float height = bottomY - topY;

                        auto ladder = std::make_unique<Ladder>(m_pOwner);
                        ladder->SetLocalPosition(x, topY);
                        ladder->SetHeight(height);
                        outLevel->AddLadder(std::move(ladder));
                    }
                    else
                    {
                        std::cerr << "Warning: Malformed ladder entry (x, topY, bottomY missing or not numbers) in " << levelName << std::endl;
                    }
                }
            }
            else
            {
                std::cerr << "Warning: 'ladders' key not found or not an array in " << levelName << std::endl;
            }

            if (data.contains("burgerPieces") && data["burgerPieces"].is_array())
            {
                for (const auto& b : data["burgerPieces"])
                {
                    if (b.is_object() && b.contains("type") && b["type"].is_string() &&
                        b.contains("position") && b["position"].is_object())
                    {
                        const auto& pos = b["position"];
                        if (pos.contains("x") && pos["x"].is_number() &&
                            pos.contains("y") && pos["y"].is_number())
                        {
                            auto burger = std::make_unique<BurgerPiece>(m_pOwner);
                            std::string typeStr = b["type"].get<std::string>();
                            burger->SetType(burger->ConvertStringToBurgerType(typeStr));
                            burger->SetLocalPosition(pos["x"].get<float>(), pos["y"].get<float>());
                            outLevel->AddBurgerPiece(std::move(burger));
                        }
                        else
                        {
                            std::cerr << "Warning: position data for a burgerPiece in " << levelName << std::endl;
                        }
                    }
                    else
                    {
                        std::cerr << "Warning: burgerPiece in " << levelName << std::endl;
                    }
                }
            }
            else
            {
                std::cerr << "Warning: 'burgerPieces' not found " << levelName << std::endl;
            }
        }
        catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON error: " << e.what() << std::endl;
        }
	}
}