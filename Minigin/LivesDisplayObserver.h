#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class LivesComponent;

	class LivesDisplayObserver final : public Observer, public Component
	{
	public:
		LivesDisplayObserver(GameObject* pOwner, TextComponent* textComp);
		virtual ~LivesDisplayObserver() = default;

		void Notify(Event event, Subject* subject) override;

		void Register(LivesComponent* livesComp);
		void Unregister(LivesComponent* livesComp);

		void Update(float deltaTime) override { (void)deltaTime; }
		void Render() const override {}
		void SetLocalPosition(float x, float y) override { (void)x; (void)y; }
	private:
		TextComponent* m_textComponent;
	};
}