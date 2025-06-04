#pragma once
template<typename Entity>
class State {
public:
    virtual ~State() = default;
    virtual void Enter(Entity* entity) = 0;
    virtual void Exit(Entity* entity) = 0;
    virtual void Update(Entity* entity, float dt) = 0;
    virtual void HandleInput(Entity* entity) = 0;
};