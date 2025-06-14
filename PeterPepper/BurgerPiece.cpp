#include "BurgerPiece.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "collisionUtils.h"
#include "Level.h"
#include "iostream"
#include "ServiceLocator.h"
#include "SoundService.h"
#include "Plate.h"

namespace dae
{
    BurgerPiece::BurgerPiece(GameObject* ownerPtr, Level* levelPtr) : 
        Component(ownerPtr),
		m_pLevel(levelPtr),
		m_lastPlatform(nullptr),
        m_localTransform(),
		m_texture(nullptr)
    {

    }

	void BurgerPiece::Update(float deltaTime)
	{
		if (!m_isFalling && IsFullyStepped())
		{
			Fall();
		}
		if (m_isFalling)
		{
			auto pos = m_localTransform.GetPosition();
			float prevY = pos.y;
			pos.y += 5.0f * deltaTime;

			glm::vec2 worldPos = GetOwner()->GetWorldTransform().GetPosition() + pos;
			glm::vec2 mySize{ m_texture->GetSize().x, static_cast<float>(m_texture->GetSize().y) };
			bool landed = false;
			
			for (auto* platform : m_pLevel->GetPlatforms())
			{
				if (platform == m_lastPlatform) continue; // Skip the last platform we landed on

				glm::vec2 platPos;
				platform->GetWorldPosition(platPos);

				float platTop = platPos.y;
				float prevBottom = GetOwner()->GetWorldTransform().GetPosition().y + prevY + mySize.y;
				float newBottom = worldPos.y + mySize.y;

				bool wasAbove = prevBottom <= platTop;
				bool isNowBelowOrAt = newBottom >= platTop;
				bool xOverlap = worldPos.x < platPos.x + platform->GetWidth() && worldPos.x + mySize.x > platPos.x;

				if (wasAbove && isNowBelowOrAt && xOverlap)
				{
					pos.y = platTop - mySize.y;
					landed = true;
					m_lastPlatform = platform;
					if(dynamic_cast<Plate*>(platform))
						m_isOnPlate = true;
					break;
				}
			}

			SetLocalPosition(pos.x, pos.y);

			if (landed)
			{
				auto* below = FindIngredientBelow();
				if (below && !below->m_isFalling && !below->IsOnPlate()) {
					below->Fall();
				}
				OnLand();
			}


			auto below = FindIngredientBelow();
			if (below) {
				if (below->m_isFalling)
					return;
				if (below->IsOnPlate())
				{
					m_isOnPlate = true;
					m_isFalling = false;
					ResetStepped();
				}
				else {
					below->Fall();
					ServiceLocator::GetSoundService()->PlaySound("Sound/BurgerLand.wav");
				}
			}
		}
	}
	void BurgerPiece::Fall()
	{
		if (m_isFalling || m_isOnPlate) return;
		m_isFalling = true;
		ServiceLocator::GetSoundService()->PlaySound("Sound/BurgerFall.wav");
	}

	void BurgerPiece::OnLand() {
		m_isFalling = false;
		ResetStepped();
		// TODO: Award score here (see next step)
	}

	BurgerPiece* BurgerPiece::FindIngredientBelow()
	{
		if (!m_pLevel) return nullptr;

		auto allPieces = m_pLevel->GetBurgerPieces();
		glm::vec2 myPos = GetOwner()->GetWorldTransform().GetPosition() + m_localTransform.GetPosition();
		glm::vec2 mySize{ m_texture->GetSize().x / 4.0f, static_cast<float>(m_texture->GetSize().y) };

		for (auto& piece : allPieces)
		{
			if (piece == this) continue; // Skip self
			glm::vec2 otherPos = piece->GetOwner()->GetWorldTransform().GetPosition() + piece->m_localTransform.GetPosition();
			glm::vec2 otherSize{ piece->m_texture->GetSize().x / 4.0f, static_cast<float>(piece->m_texture->GetSize().y) };
			if (IsAABBOverlap(myPos, mySize, otherPos, otherSize))
			{
				return piece;
			}
		}
		return nullptr;
	}



	void dae::BurgerPiece::Render() const
	{
		//TODO: Find proper way to calculate this
		if (!m_texture) return;
		const auto texSize = m_texture->GetSize();
		const float partWidth = texSize.x / 4.0f;
		const float w = partWidth;
		const float h = static_cast<float>(texSize.y);

		// Calculate offsets for each tile
		int offsets[4] = { 0, 0, 0, 0 };

		// First, give each stepped tile a base offset of 1
		for (int i = 0; i < 4; ++i) {
			offsets[i] = m_stepped[i];
		}

		// Ends extra offset for the first and last tile
		if (m_stepped[0]) {
			offsets[0] += m_stepped[1];
		}
		if (m_stepped[3]) {
			offsets[3] += m_stepped[2];
		}

		// Middle extras
		if (m_stepped[1]) {
			if (m_stepped[2] && m_stepped[3]) {
				offsets[2] += 1;
				offsets[3] += 1;
			}
		}

		if (m_stepped[2]) {
			if (m_stepped[0] && m_stepped[1]) {
				offsets[0] += 1;
				offsets[1] += 1;
			}
		}

		const auto pos = GetOwner()->GetWorldTransform().GetPosition() + m_localTransform.GetPosition();
		for (int i = 0; i < 4; ++i) {
			SDL_Rect srcRect{};
			srcRect.x = static_cast<int>(i * partWidth);
			srcRect.y = 0;
			srcRect.w = static_cast<int>(partWidth);
			srcRect.h = texSize.y;

			float drawX = pos.x + i * partWidth;
			float drawY = pos.y + static_cast<float>(offsets[i]);

			Renderer::GetInstance().RenderTexture(*m_texture, &srcRect, drawX, drawY, w, h);
		}
	}

	void BurgerPiece::SetType(BurgerPieceType type) 
	{ 
		m_type = type; 
		switch (type)
		{
			case BurgerPieceType::TopBun:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerTopBun.png");
				break;
			case BurgerPieceType::Lettuce:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerLettuce.png");
				break;
			case BurgerPieceType::Patty:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerPatty.png");
				break;
			case BurgerPieceType::Tomato:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerTomato.png");
				break;
			case BurgerPieceType::Cheese:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerCheese.png");
				break;
			case BurgerPieceType::BottomBun:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerBottomBun.png");
				break;
			default:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerTopBun.png");
				break;
		}
	}

	BurgerPieceType BurgerPiece::ConvertStringToBurgerType(const std::string& typeStr)
	{
		if (typeStr == "TopBun") {
			return BurgerPieceType::TopBun;
		}
		else if (typeStr == "Lettuce") {
			return BurgerPieceType::Lettuce;
		}
		else if (typeStr == "Patty") {
			return BurgerPieceType::Patty;
		}
		else if (typeStr == "Tomato") {
			return BurgerPieceType::Tomato;
		}
		else if (typeStr == "Cheese") {
			return BurgerPieceType::Cheese;
		}
		else if (typeStr == "BottomBun") {
			return BurgerPieceType::BottomBun;
		}
		return BurgerPieceType::TopBun;
	}

	void BurgerPiece::SetLocalPosition(float x, float y)
	{
        m_localTransform.SetPosition(x, y, 0);
	}

	void BurgerPiece::SetStepped(int part)
	{
		if(m_stepped[part])
			return;

		if (part >= 0 && part < 4) {
			m_stepped[part] = true;
			ServiceLocator::GetSoundService()->PlaySound("Sound/BurgerStep.wav");
		}
	}

	bool BurgerPiece::IsStepped(int part) const
	{
		if (part >= 0 && part < 4) {
			return m_stepped[part];
		}
		return false;
	}

	bool BurgerPiece::IsFullyStepped() const
	{
		for (int i = 0; i < 4; ++i) {
			if (!m_stepped[i]) {
				return false;
			}
		}
		return true;
	}

	void BurgerPiece::ResetStepped()
	{
		for (int i{0}; i < 4; ++i) {
			m_stepped[i] = false;
		}
	}

	void dae::BurgerPiece::CheckAndSetStepped(const glm::vec2& playerPos, const glm::vec2& playerSize)
	{
		glm::vec3 burgerPos = m_localTransform.GetPosition();
		glm::ivec2 burgerSize = m_texture ? m_texture->GetSize() : glm::ivec2(32, 8); // fallback size

		float partWidth = static_cast<float>(burgerSize.x) / 4.0f;
		float partHeight = static_cast<float>(burgerSize.y);

		for (int i = 0; i < 4; ++i)
		{
			if (IsStepped(i))
				continue;

			// Each part is laid out horizontally
			float partX = burgerPos.x + i * partWidth;
			glm::vec2 partPos(partX, burgerPos.y);
			glm::vec2 partSize(partWidth, partHeight);

			bool overlap = IsAABBOverlap(playerPos, playerSize, partPos, partSize);

			if (overlap)
			{
				SetStepped(i);
			}
		}
	}

}