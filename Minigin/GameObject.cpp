#include <string>
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <ranges>
#include <algorithm>

namespace dae 
{
	void GameObject::Update(const float deltaTime)
	{
		for (auto& component : m_components)
		{
			component->Update(deltaTime);
		}
	}

	void GameObject::Render() const
	{
		for (const auto& component : m_components)
		{
			component->Render();
		}
	}

	void GameObject::SetLocalPosition(float x, float y)
	{
		m_localTransform.SetPosition(x, y, 0.0f);
	}

	void GameObject::SetLocalPosition(const glm::vec3& pos)
	{
		m_localTransform.SetPosition(pos);
	}

	Transform GameObject::GetWorldTransform()
	{
		if (m_positionIsDirty)
		{
			UpdateWorldPosition();
		}
		return m_worldTransform;
	}

	void GameObject::UpdateWorldPosition()
	{
		if (m_pParent == nullptr)
		{
			m_worldTransform.SetPosition(m_localTransform.GetPosition());
		}
		else
		{
			m_worldTransform.SetPosition(m_pParent->GetWorldTransform().GetPosition());
		}
		m_positionIsDirty = false;
	}

	void GameObject::SetPositionIsDirty()
	{
		m_positionIsDirty = true;

		for (const auto& child : m_children)
		{
			child->SetPositionIsDirty();
		}
	}

	void GameObject::SetParent(GameObject* pNewParent, bool worldPositionStays)
	{
		if (m_pParent == nullptr)
		{
			SetLocalPosition(GetWorldTransform().GetPosition());
		}
		else
		{
			if (worldPositionStays)
			{
				SetLocalPosition(GetWorldTransform().GetPosition() - m_pParent->GetWorldTransform().GetPosition());
			}
			SetPositionIsDirty();
		}

		if (m_pParent)
		{
			auto& childrenVec = m_pParent->GetChildrenVector();

			auto thisChild = std::ranges::find_if(childrenVec, [this](const auto& child)
			{
				return child == this;
			});

			childrenVec.erase(thisChild);
		}

		m_pParent = pNewParent;

		if (m_pParent)
		{
			auto& childrenVec = m_pParent->GetChildrenVector();
			childrenVec.push_back(this);
		}
	}

	std::vector<dae::GameObject*>& dae::GameObject::GetChildrenVector()
	{
		return m_children;
	}

	dae::GameObject* dae::GameObject::GetParent() const
	{
		return m_pParent;
	}

	void GameObject::Destroy()
	{
		m_markedToDestroy = true;

		for (const auto child : m_children)
		{
			child->Destroy();
		}
	}

	bool GameObject::IsMarkedToDestroy() const
	{
		return m_markedToDestroy;
	}
}