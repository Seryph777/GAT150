#pragma once
#include "Font.h"
#include "Core/Color.h"
#include <string>
#include <memory>
struct SDL_Texture;

namespace kiko
{
	class Renderer;
	class Text
	{
	public:
		/*<create a default constructor>*/
		Text() = default;
		Text(std::shared_ptr<Font> font) : m_font{ font } { }
		~Text();
		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, int x, int y);
	private:
		std::shared_ptr<Font> m_font;
		SDL_Texture* m_texture = nullptr;
	};
}