#pragma once
#include "Component.h"
#include "Transform.h"
#include "TextureComponent.h"
#include <memory>
#include <string>

namespace dae
{
    enum class BurgerPieceType { 
        TopBun, 
        Lettuce, 
        Patty, 
        Tomato,
		Cheese,
        BottomBun 
    };

	class BurgerPiece : public Component
    {
    public:
        explicit BurgerPiece(GameObject* ownerPtr);

        BurgerPiece(const BurgerPiece& other) = delete;
        BurgerPiece(BurgerPiece&& other) = delete;
        BurgerPiece& operator=(const BurgerPiece& other) = delete;
        BurgerPiece& operator=(BurgerPiece&& other) = delete;

        void Update(float deltaTime);
        void Render() const;

        void SetLocalPosition(float x, float y) override;
        void SetType(BurgerPieceType type);
        BurgerPieceType ConvertStringToBurgerType(const std::string& typeStr);

        BurgerPieceType GetType() const { return m_type; }
        int GetScoreValue() const { return m_scoreValue; }
        bool IsCollected() const { return m_isCollected; }
        void SetCollected(bool collected) { m_isCollected = collected; }

	private:
        Transform m_localTransform;
		BurgerPieceType m_type;
		std::shared_ptr<Texture2D> m_texture;
		int m_scoreValue{ 100 };
		bool m_isCollected{ false };
    };
}