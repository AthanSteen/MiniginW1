#include "Plate.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

namespace dae
{
	Plate::Plate(GameObject* ownerPtr)
		: Platform(ownerPtr)
	{
		m_texturePlate = ResourceManager::GetInstance().LoadTexture("Level/Plate.png");
	}

	void Plate::Render() const
	{
		if (!m_texturePlate) return;
		const auto pos = GetOwner()->GetWorldTransform().GetPosition() + m_localTransform.GetPosition();
		auto texSize = m_texturePlate->GetSize();
		float x = pos.x;
		float y = pos.y;
		float w = static_cast<float>(texSize.x);
		float h = static_cast<float>(texSize.y);
		Renderer::GetInstance().RenderTexture(*m_texturePlate, nullptr, x, y, w, h);
	}
}