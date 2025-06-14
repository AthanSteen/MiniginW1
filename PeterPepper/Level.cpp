#include "Level.h"
#include "Platform.h"

namespace dae
{
	Level::Level(GameObject* ownerPtr)
		: Component(ownerPtr),
		m_playerSpawn(0.0f, 0.0f)
    {

    }

    void Level::Update(float deltaTime)
    {
		for (const auto& platform : m_platforms)
		{
			platform->Update(deltaTime);
		}
		for (const auto& ladder : m_ladders)
		{
			ladder->Update(deltaTime);
		}
		for (const auto& piece : m_burgerPieces)
		{
			piece->Update(deltaTime);
		}
    }

    void Level::Render() const
    {
		for (const auto& platform : m_platforms)
		{
			platform->Render();
		}
		for (const auto& ladder : m_ladders)
		{
			ladder->Render();
		}
		for (const auto& piece : m_burgerPieces)
		{
			piece->Render();
		}
	}

	void Level::AddPlatform(std::unique_ptr<Platform> platform)
	{
		if (platform)
		{
			m_platforms.push_back(std::move(platform));
		}
	}
	void Level::AddLadder(std::unique_ptr<Ladder> ladder)
	{
		if (ladder)
		{
			m_ladders.push_back(std::move(ladder));
		}
	}
	void Level::AddBurgerPiece(std::unique_ptr<BurgerPiece> piece)
	{
		if (piece)
		{
			m_burgerPieces.push_back(std::move(piece));
		}
    }

	bool Level::isOverlappingPlatform(const glm::vec2& playerPos, const glm::vec2& playerSize) const
	{
		for (const auto& platform : m_platforms)
		{
			if (platform->IsOverlapping(playerPos, playerSize))
			{
				return true;
			}
		}
		return false;
	}

	bool Level::isOverlappingLadders(const glm::vec2& playerPos, const glm::vec2& playerSize) const
	{
		for (const auto& ladder : m_ladders)
		{
			if (ladder->IsOverlapping(playerPos, playerSize))
			{
				return true;
			}
		}
		return false;
	}
}