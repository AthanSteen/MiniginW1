#pragma once
#include "ScoreDisplayObserver.h"
#include "ScoreComponent.h"

namespace dae
{
	ScoreDisplayObserver::ScoreDisplayObserver(GameObject* pOwner, TextComponent* textComp)
		: Component(pOwner), m_textComponent(textComp) {}

	void ScoreDisplayObserver::Notify(Event event, Subject* subject)
	{
		if (event == Event::ScoreChanged)
		{
			auto scoreComp = dynamic_cast<ScoreComponent*>(subject);
			if (scoreComp)
			{
				m_textComponent->SetText("Score: " + std::to_string(scoreComp->GetScore()));
			}
		}
	}

	void ScoreDisplayObserver::Register(ScoreComponent* scoreComp)
	{
		scoreComp->AddObserver(this);
	}

	void ScoreDisplayObserver::Unregister(ScoreComponent* scoreComp)
	{
		scoreComp->RemoveObserver(this);
	}
}