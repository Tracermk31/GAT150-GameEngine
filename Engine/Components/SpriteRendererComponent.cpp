#include "pch.h"

#include "Engine.h"
#include "SpriteRendererComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(SpriteRendererComponent)

	/// <summary>
	/// Function to draw the texture onto a screen using a provided renderer. Retrieves all necessary texture
	/// information from the m_texture member variable and position and size information from the m_owner member variable.
	/// </summary>
	/// <param name="renderer">The Renderer used to draw the texture</param>
	void SpriteRendererComponent::Draw(const Renderer& renderer) const {
		if (m_texture) {
			renderer.DrawTexture(*m_texture,
				GetOwner()->GetTransform().position.x,
				GetOwner()->GetTransform().position.y,
				GetOwner()->GetTransform().rotation,
				GetOwner()->GetTransform().scale);
		}
	}

	/// <summary>
	/// Reads texture informatoin from a provided JSON file
	/// </summary>
	/// <param name="value">JSON value to be read from</param>
	void SpriteRendererComponent::Read(const JSON::value_t& value) {
		RendererComponent::Read(value);

		std::string textureName;
		JSON_READ_MEMBER(value, "texture", textureName);
		if (!textureName.empty()) {
			m_texture = Resources().Get<Texture>(textureName, G_Engine().GetRenderer());
		}
	}
}