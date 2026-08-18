#include "pch.h"

#include "Engine.h"
#include "SpriteRendererComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::Draw(const Renderer& renderer) const {
		if (m_texture) {
			renderer.DrawTexture(*m_texture,
				GetOwner()->GetTransform().position.x,
				GetOwner()->GetTransform().position.y,
				GetOwner()->GetTransform().rotation,
				GetOwner()->GetTransform().scale);
		}
	}

	void SpriteRendererComponent::Read(const JSON::value_t& value) {
		RendererComponent::Read(value);

		std::string textureName;
		JSON_READ_MEMBER(value, "texture", textureName);
		if (!textureName.empty()) {
			m_texture = Resources().Get<Texture>(textureName, G_Engine().GetRenderer());
		}
	}
}