#include "BurgerPiece.h"
#include "GameObject.h"
#include "ResourceManager.h"

namespace dae
{
    BurgerPiece::BurgerPiece(GameObject* ownerPtr) : 
        Component(ownerPtr),
        m_localTransform(),
		m_texture(nullptr)
    {

    }

    void BurgerPiece::Update(float /*deltaTime*/)
    {

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
				m_scoreValue = 100;
				break;
			case BurgerPieceType::Lettuce:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerLettuce.png");
				m_scoreValue = 100;
				break;
			case BurgerPieceType::Patty:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerPatty.png");
				m_scoreValue = 100;
				break;
			case BurgerPieceType::Tomato:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerTomato.png");
				m_scoreValue = 100;
				break;
			case BurgerPieceType::Cheese:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerCheese.png");
				m_scoreValue = 100;
				break;
			case BurgerPieceType::BottomBun:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerBottomBun.png");
				m_scoreValue = 100;
				break;
			default:
				m_texture = ResourceManager::GetInstance().LoadTexture("Level/BurgerTopBun.png");
				m_scoreValue = 100;
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
		if (part >= 0 && part < 4) {
			m_stepped[part] = true;
		}
	}

	bool BurgerPiece::IsStepped(int part) const
	{
		if (part >= 0 && part < 4) {
			return m_stepped[part];
		}
		return false;
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

			// AABB collision
			bool overlap =
				playerPos.x < partPos.x + partSize.x &&
				playerPos.x + playerSize.x > partPos.x &&
				playerPos.y < partPos.y + partSize.y &&
				playerPos.y + playerSize.y > partPos.y;

			if (overlap)
			{
				SetStepped(i);
				// TODO: Drop logic
			}
		}
	}

}