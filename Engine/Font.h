#pragma once

#include  <string>

struct TTF_Font;

namespace ChiefEngine {
	class Font {
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

		TTF_Font* getFont() {
			return m_ttfFont;
		}

	private:
		friend class Text;

		TTF_Font* m_ttfFont{ nullptr };
	};
}

