#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class ScoreComponent;

	class ScoreDisplayObserver final : public Observer, public Component
	{
	public:
		ScoreDisplayObserver(GameObject* pOwner, TextComponent* textComp);
		virtual ~ScoreDisplayObserver() = default;

		void Notify(Event event, Subject* subject) override;

		void Register(ScoreComponent* livesComp);
		void Unregister(ScoreComponent* livesComp);

		void Update(float deltaTime) override { (void)deltaTime; }
		void Render() const override {}
		void SetLocalPosition(float x, float y) override { (void)x; (void)y; }
	private:
		TextComponent* m_textComponent;
	};
}