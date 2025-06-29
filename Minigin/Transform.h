#pragma once
#include <glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& pos);
	private:
		glm::vec3 m_position;
	};
}
