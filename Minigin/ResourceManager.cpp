#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

namespace fs = std::filesystem;

void dae::ResourceManager::Init()
{
	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(const std::string& file)
{
	if (!m_loadedTextures.contains(file))
	{
		m_loadedTextures.insert(std::pair(file, std::make_shared<Texture2D>(file)));
	}
	return m_loadedTextures.at(file);
}

std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, uint8_t size)
{
	const auto key = std::pair<std::string, uint8_t>(file, size);

	if (!m_loadedFonts.contains(key))
	{
		m_loadedFonts.insert(std::pair(key, std::make_shared<Font>(file, size)));
	}
	return m_loadedFonts.at(key);
}

void dae::ResourceManager::UnloadUnusedResources()
{
	for (auto it = m_loadedTextures.begin(); it != m_loadedTextures.end();)
	{
		if (it->second.use_count() == 1)
			it = m_loadedTextures.erase(it);
		else
			++it;
	}

	for (auto it = m_loadedFonts.begin(); it != m_loadedFonts.end();)
	{
		if (it->second.use_count() == 1)
			it = m_loadedFonts.erase(it);
		else
			++it;
	}
}
