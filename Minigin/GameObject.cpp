#include <string>
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::GameObject::Update(const float deltaTime)
{
	for (auto& component : m_components)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_components)
	{
		component->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::Destroy()
{
	m_MarkedToDestroy = true;

	//for (const auto child : m_Children)
	//{
	//	child->Destroy();
	//}
}

bool dae::GameObject::IsMarkedToDestroy() const
{
	return m_MarkedToDestroy;
}