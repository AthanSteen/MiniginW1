#pragma once
#include "SoundService.h"
#include <memory>

namespace dae
{
    class ServiceLocator
    {
    public:
        static void RegisterSoundService(std::unique_ptr<SoundService> service)
        {
            m_pSoundService = std::move(service);
        }

        static SoundService* GetSoundService()
        {
            return m_pSoundService.get();
        }

    private:
        static inline std::unique_ptr<SoundService> m_pSoundService{};
    };
}