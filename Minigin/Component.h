#pragma once

namespace dae
{
    class GameObject;

    class Component
    {
    public:
        virtual ~Component() = default;

        Component(const Component& other) = delete;
        Component(Component&& other) = delete;
        Component& operator=(const Component& other) = delete;
        Component& operator=(Component&& other) = delete;

        virtual void Update(float deltaTime) = 0;
        virtual void Render() const = 0;

        virtual void SetLocalPosition(float x, float y) = 0;
        virtual void Destroy() { m_markedToDestroy = true; }
		virtual bool IsMarkedToDestroy() const { return m_markedToDestroy; }
    protected:
        explicit Component(GameObject* pOwner) : m_pOwner(pOwner), m_markedToDestroy(false) {}
        GameObject* GetOwner() const { return m_pOwner; }
    private:
        GameObject* m_pOwner;
        bool m_markedToDestroy;
    };
}
