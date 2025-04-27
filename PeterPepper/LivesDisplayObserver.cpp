#pragma once
#include "LivesDisplayObserver.h"
#include "LivesComponent.h"

namespace dae
{
	LivesDisplayObserver::LivesDisplayObserver(GameObject* pOwner, TextComponent* textComp) 
		: Component(pOwner), m_textComponent(textComp) {}

	void LivesDisplayObserver::Notify(Event event, Subject* subject)
	{
		if (event == Event::PlayerDied)
		{
			auto livesComp = dynamic_cast<LivesComponent*>(subject);
			if (livesComp)
			{
				m_textComponent->SetText("Lives: " + std::to_string(livesComp->GetLives()));
			}
		}
	}

	void LivesDisplayObserver::Register(LivesComponent* livesComp)
	{
		livesComp->AddObserver(this);
	}

	void LivesDisplayObserver::Unregister(LivesComponent* livesComp)
	{
		livesComp->RemoveObserver(this);
	}
}