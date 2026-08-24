#pragma once

#include "Renderer/Texture.h"
#include "Resources/Resource.h"
#include "RendererComponent.h"

namespace ChiefEngine {
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent)

		void Draw(const Renderer& renderer) const override;

		void Read(const JSON::value_t& value) override;

		/// <summary>
		/// Getter for the m_texture member variable that stores the information necessary for a texture
		/// </summary>
		/// <returns>m_texture member value</returns>
		inline const resource_t<Texture> GetTexture() {
			return m_texture;
		}

	protected:
		resource_t<Texture> m_texture;
	};
}