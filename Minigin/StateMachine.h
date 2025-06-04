#include "State.h"

template<typename Entity>
class StateMachine {
public:
    State<Entity>* currentState = nullptr;

    void ChangeState(Entity* entity, State<Entity>* newState) {
        if (currentState)
            currentState->Exit(entity);
        currentState = newState;
        if (currentState)
            currentState->Enter(entity);
    }

    void Update(Entity* entity, float dt) {
        if (currentState)
            currentState->Update(entity, dt);
    }

    void HandleInput(Entity* entity) {
        if (currentState)
            currentState->HandleInput(entity);
    }
};