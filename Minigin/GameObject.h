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

		void SetPosition(float x, float y);
		const Transform& GetTransform() const { return m_transform; };

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
		bool m_MarkedToDestroy{ };

		Transform m_transform{};

		std::vector<std::unique_ptr<Component>> m_components;
	};
}
