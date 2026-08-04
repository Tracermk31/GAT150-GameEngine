#pragma once

#include "Vector2.h"

#include <string>

struct SDL_Texture;

namespace ChiefEngine {

	class Renderer;

	class Texture
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, Renderer& renderer);

		Vector2 GetSize();

		friend Renderer;

	private:
		SDL_Texture* m_texture{ nullptr };
	};

}