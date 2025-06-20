#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "implot.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
	ImPlot::CreateContext();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}

	ImPlot::DestroyContext();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	dae::Renderer::RenderTexture(texture, nullptr, x, y);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	dae::Renderer::RenderTexture(texture, nullptr, x, y, width, height);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect* srcRect, const float x, const float y) const
{
	glm::ivec2 size;
	if (srcRect)
		size = { srcRect->w, srcRect->h };
	else
		size = texture.GetSize();

	RenderTexture(texture, srcRect, x, y, static_cast<float>(size.x), static_cast<float>(size.y));

}

void dae::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect* srcRect, const float x, const float y, const float width, const float height, bool flipToRight) const
{
	float zoom = GetZoom();

	SDL_Rect dst{};
	dst.x = static_cast<int>(x * zoom);
	dst.y = static_cast<int>(y * zoom);
	dst.w = static_cast<int>(width * zoom);
	dst.h = static_cast<int>(height * zoom);

	if (flipToRight)
	{
		SDL_Point* center = NULL;
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), srcRect, &dst, 0, center, SDL_FLIP_HORIZONTAL);
	}
	else
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), srcRect, &dst);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
