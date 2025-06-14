#pragma once
#include "Platform.h"


namespace dae
{
	class Plate : public Platform
	{
	public:
		explicit Plate(GameObject* ownerPtr);

		Plate(const Plate& other) = delete;
		Plate(Plate&& other) = delete;
		Plate& operator=(const Plate& other) = delete;
		Plate& operator=(Plate&& other) = delete;

		void Render() const override;

	private:
		std::shared_ptr<Texture2D> m_texturePlate;
	};
}

