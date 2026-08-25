#pragma once

#include "RendererComponent.h"
#include "Resources/ResourceManager.h"

namespace ChiefEngine {
	class SpriteAnimationRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteAnimationRendererComponent)

		virtual void Draw(const class Renderer& renderer) const override;
		void Update(float dt) override;
		void Read(const JSON::value_t& value) override;
	private:
		unsigned short m_currentFrame;
		float m_framesPerSecond = 30.0f;
		bool m_looping = true;

		float m_frameTimer = 0;

		resource_t<class TextureFrames> m_textureFrames;
	};
}