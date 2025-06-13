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

    void BurgerPiece::Render() const
    {
		if (!m_texture) return;

		SDL_Rect srcRect{};
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = m_texture->GetSize().x;
		srcRect.h = m_texture->GetSize().y;
		const float w = static_cast<float>(srcRect.w);
		const float h = static_cast<float>(srcRect.h);
		const auto pos = GetOwner()->GetWorldTransform().GetPosition() + m_localTransform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, &srcRect, pos.x, pos.y, w, h);
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
}