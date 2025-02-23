#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "Transform.h"

namespace dae
{
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(const float deltaTime);
		void Render() const;

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec3& pos);
		void SetParent(GameObject* pNewParent, bool worldPositionStays);
		std::vector<GameObject*>& GetChildrenVector();

		Transform GetWorldTransform();
		GameObject* GetParent() const;
		void SetPositionIsDirty();

		void Destroy();
		bool IsMarkedToDestroy() const;

		template <typename ComponentType, typename... Args>
			requires std::derived_from<ComponentType, Component>
		ComponentType* AddComponent(Args&&... args)
		{
			auto component = std::make_unique<ComponentType>(this, std::forward<Args>(args)...);
			ComponentType* rawPtr = component.get();
			m_components.emplace_back(std::move(component));
			return rawPtr;
		}

		template <typename ComponentType>
			requires std::derived_from<ComponentType, Component>
		ComponentType* GetComponent() const
		{
			for (const auto& comp : m_components)
			{
				if (ComponentType* casted = dynamic_cast<ComponentType*>(comp.get()))
					return casted;
			}
			return nullptr;
		}

		template <typename ComponentType>
			requires std::derived_from<ComponentType, Component>
		void DeleteComponent() const
		{
			for (const auto& component : m_components)
			{
				if (ComponentType* casted = dynamic_cast<ComponentType*>(component.get()))
				{
					component->Destroy();
					break;
				}
			}
		}

	private:
		void UpdateWorldPosition();

		bool m_positionIsDirty{ true };
		bool m_markedToDestroy{ };

		Transform m_localTransform{ };
		Transform m_worldTransform{ };
		GameObject* m_pParent{ nullptr };

		std::vector<std::unique_ptr<Component>> m_components;
		std::vector<GameObject*> m_children;
	};
}
