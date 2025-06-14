#pragma once
#include <string>

namespace dae
{
	class SoundService
	{
	public:
		virtual ~SoundService() = default;
		virtual void PlaySound(const std::string& soundFile, bool loop = false) = 0;
		virtual void StopAllSounds() = 0; 
		virtual void MuteAll() = 0;
		virtual void UnmuteAll() = 0;
	};
}