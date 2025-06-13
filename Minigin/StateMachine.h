#pragma once
#include <memory>
#include "State.h"

template<typename Entity>
class StateMachine {
public:
    void ChangeState(std::unique_ptr<State<Entity>> newState) {
        if (m_currentState && (typeid(*m_currentState) == typeid(*newState)))
            return; // Avoid changing to the same state
        m_nextState = std::move(newState);
    }

    void Update(Entity* entity, float dt) {
        ProcessPendingChange(entity);
        if (m_currentState)
            m_currentState->Update(entity, dt);
    }

    void HandleInput(Entity* entity) {
        if (m_currentState)
            m_currentState->HandleInput(entity);
    }
private:
    std::unique_ptr<State<Entity>> m_currentState = nullptr;
    std::unique_ptr<State<Entity>> m_nextState = nullptr;

    void ProcessPendingChange(Entity* entity) {
        if (m_nextState) {
            if (m_currentState)
                m_currentState->Exit(entity);

            m_currentState = std::move(m_nextState);
            m_currentState->Enter(entity);
        }
    }
};
