#pragma once
#include "Component.h"
#include "Transform.h"
#include "TextureComponent.h"
#include <memory>
#include <string>
#include <glm.hpp>

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
        
        void SetStepped(int part);
        bool IsStepped(int part) const;
		void ResetStepped();

        void CheckAndSetStepped(const glm::vec2& playerPos, const glm::vec2& playerSize);
	private:
        Transform m_localTransform;
		BurgerPieceType m_type;
		std::shared_ptr<Texture2D> m_texture;
		int m_scoreValue{ 100 };
		bool m_stepped[4]{ false, false, false, false };
    };
}