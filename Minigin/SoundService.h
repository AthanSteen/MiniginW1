#pragma once
#include <string>

namespace dae
{
	class SoundService
	{
	public:
		virtual ~SoundService() = default;
		virtual void PlaySound(const std::string& soundFile) = 0;
		virtual void StopAllSounds() = 0;
	};
}