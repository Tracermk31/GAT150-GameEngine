#pragma once

#include "Font.h"
#include "Vector3.h"

struct SDL_Texture;

namespace ChiefEngine {
	class Renderer;

	class Text {
	public:
		Text() = default;
		Text(Font* font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, float x, float y) const;

	private:
		Font* m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};

}
