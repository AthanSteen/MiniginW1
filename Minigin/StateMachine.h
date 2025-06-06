#pragma once
#include <memory>
#include "State.h"

template<typename Entity>
class StateMachine {
public:
    void ChangeState(std::unique_ptr<State<Entity>> newState) {
        nextState = std::move(newState);
    }

    void Update(Entity* entity, float dt) {
        ProcessPendingChange(entity);
        if (currentState)
            currentState->Update(entity, dt);
    }

    void HandleInput(Entity* entity) {
        if (currentState)
            currentState->HandleInput(entity);
    }
private:
    std::unique_ptr<State<Entity>> currentState = nullptr;
    std::unique_ptr<State<Entity>> nextState = nullptr;

    void ProcessPendingChange(Entity* entity) {
        if (nextState) {
            if (currentState)
                currentState->Exit(entity);

            currentState = std::move(nextState);
            currentState->Enter(entity);
        }
    }
};
