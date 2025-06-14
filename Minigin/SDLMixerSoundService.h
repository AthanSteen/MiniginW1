#pragma once
#include "SoundService.h"
#include <memory>
#include <vector>
#include <mutex>
#include <SDL_mixer.h>

namespace dae
{
    class SDLMixerSoundService final : public SoundService
    {
    public:
        SDLMixerSoundService();
        ~SDLMixerSoundService() override;

        void PlaySound(const std::string& soundFile, bool loop = false) override;
        void StopAllSounds() override;
        void MuteAll() override;
        void UnmuteAll() override;

    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
        std::mutex m_PlayingMutex;
        std::vector<std::pair<int, Mix_Chunk*>> m_PlayingSounds;
    };
}