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

    class Level;
	class Platform;
	class BurgerPiece : public Component
    {
    public:
        explicit BurgerPiece(GameObject* ownerPtr, Level* levelPtr);

        BurgerPiece(const BurgerPiece& other) = delete;
        BurgerPiece(BurgerPiece&& other) = delete;
        BurgerPiece& operator=(const BurgerPiece& other) = delete;
        BurgerPiece& operator=(BurgerPiece&& other) = delete;

        void Update(float deltaTime) override;
        void Render() const override;

        void SetLocalPosition(float x, float y) override;
        void SetType(BurgerPieceType type);
        BurgerPieceType ConvertStringToBurgerType(const std::string& typeStr);

        BurgerPieceType GetType() const { return m_type; }
        int GetScoreValue() const { return m_scoreValue; }
        
        void SetStepped(int part);
        bool IsStepped(int part) const;
        bool IsFullyStepped() const;
		void ResetStepped();

		bool IsOnPlate() const { return m_isOnPlate; }

        void Fall();

        void CheckAndSetStepped(const glm::vec2& playerPos, const glm::vec2& playerSize);
	private:
        Transform m_localTransform;
		BurgerPieceType m_type;
		std::shared_ptr<Texture2D> m_texture;
		Level* m_pLevel;
        Platform* m_lastPlatform;
		int m_scoreValue{ 50 };
		bool m_stepped[4]{ false, false, false, false };
        bool m_isFalling;
        bool m_isOnPlate;

        void OnLand();
        BurgerPiece* FindIngredientBelow();
    };
}