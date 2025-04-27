#include "SDLMixerSoundService.h"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

//TODO: maybe add volume control

namespace dae
{
    class SDLMixerSoundService::Impl
    {
    public:
        Impl()
        {
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
            m_Thread = std::thread(&Impl::ProcessQueue, this);
        }

        ~Impl()
        {
            m_Stop = true;
            m_Condition.notify_all();
            if (m_Thread.joinable())
            {
                m_Thread.join();
            }
            Mix_CloseAudio();
        }

        void EnqueueSound(const std::string& soundFile)
        {
            {
                std::lock_guard lock(m_Mutex);
                m_SoundQueue.push(soundFile);
            }
            m_Condition.notify_one();
        }

        void StopAll()
        {
            Mix_HaltChannel(-1);
        }

        void CleanupFinishedSounds()
        {
            std::lock_guard lock(m_PlayingMutex);

            auto soundIterator = m_PlayingSounds.begin();
            while (soundIterator != m_PlayingSounds.end())
            {
                if (!Mix_Playing(soundIterator->first))
                {
                    Mix_FreeChunk(soundIterator->second);
                    soundIterator = m_PlayingSounds.erase(soundIterator);
                }
                else
                {
                    ++soundIterator;
                }
            }
        }

        void ProcessQueue()
        {
            while (!m_Stop)
            {
                {
                    std::unique_lock lock(m_Mutex);
                    m_Condition.wait(lock, [this] { return !m_SoundQueue.empty() || m_Stop; });

                    while (!m_SoundQueue.empty())
                    {
                        auto soundFile = m_SoundQueue.front();
                        m_SoundQueue.pop();
                        lock.unlock();

                        Mix_Chunk* sound = Mix_LoadWAV(soundFile.c_str());
                        if (sound)
                        {
                            int channel = Mix_PlayChannel(-1, sound, 0);
                            if (channel != -1)
                            {
                                std::lock_guard playingLock(m_PlayingMutex);
                                m_PlayingSounds.push_back({ channel, sound });
                            }
                            else
                            {
                                Mix_FreeChunk(sound);
                            }
                        }

                        lock.lock();
                    }
                }

                CleanupFinishedSounds();
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); // avoid spinning CPU
            }
        }

    private:
        std::thread m_Thread;
        std::queue<std::string> m_SoundQueue;
        std::mutex m_Mutex;
        std::condition_variable m_Condition;
        bool m_Stop = false;

        std::mutex m_PlayingMutex;
        std::vector<std::pair<int, Mix_Chunk*>> m_PlayingSounds;
    };

    SDLMixerSoundService::SDLMixerSoundService()
        : m_pImpl{ std::make_unique<Impl>() }
    {
    }

    SDLMixerSoundService::~SDLMixerSoundService() = default;

    void SDLMixerSoundService::PlaySound(const std::string& soundFile)
    {
        m_pImpl->EnqueueSound(soundFile);
    }

    void SDLMixerSoundService::StopAllSounds()
    {
        m_pImpl->StopAll();
    }
}
