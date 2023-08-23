#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include <SDL2-2.28.1/include/SDL_image.h>

namespace kiko
{
	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}
	bool Texture::Create(std::string filename, ...)
	{
		va_list args;
		va_start(args, filename);
		Renderer& renderer = va_arg(args, Renderer);

		va_end(args);

		return Load(filename, renderer);
	}
	bool Texture::Load(const std::string& filename, Renderer& renderer)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			// LOG_WARNING
			WARNING_LOG("failed to locate file")
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			// LOG_WARNING
			WARNING_LOG("Texture failed to load")
			return false;
		}
		return true;
	}
	vec2 Texture::GetSize()
	{
		
		ASSERT_LOG((this->m_texture != nullptr), "Texture is NULL");
		SDL_Point point;

		// https://wiki.libsdl.org/SDL2/SDL_QueryTexture //
		SDL_QueryTexture(this->m_texture, nullptr, nullptr, &point.x, &point.y);
		return vec2{ point.x, point.y };
	}
}