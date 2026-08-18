#pragma once

#include "Texture.h"
#include "Resource.h"
#include "RendererComponent.h"

namespace ChiefEngine {
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent)

		void Draw(const Renderer& renderer) const override;

		void Read(const JSON::value_t& value) override;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		inline const resource_t<Texture> GetTexture() {
			return m_texture;
		}

	protected:
		resource_t<Texture> m_texture;
	};
}