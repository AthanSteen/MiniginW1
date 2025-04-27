#pragma once
#include "Command.h"

class GameActor {
public:
	void Move();
};

class GameActorCommand : public Command {
	GameActor* m_actor;
protected:
	GameActor* GetGameActor() const { return m_actor; }
public:
	GameActorCommand(GameActor* actor);
	virtual ~GameActorCommand();
};

class Move : public GameActorCommand {
public:
	void Execute() override
	{
		GetGameActor()->Move();
	}
};