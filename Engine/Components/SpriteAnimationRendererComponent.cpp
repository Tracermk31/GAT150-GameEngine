#include "pch.h"

#include "Engine.h"
#include "SpriteAnimationRendererComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(SpriteAnimationRendererComponent)

	void SpriteAnimationRendererComponent::Update(float dt) {
		m_frameTimer += dt;
		float frameTime = 1.0f/m_framesPerSecond;

		while (m_frameTimer >= frameTime) {
			m_currentFrame++;
			if (m_looping) {
				m_currentFrame %= m_textureFrames->GetTotalFrames();
			}
			else {
				if (m_currentFrame >= m_textureFrames->GetTotalFrames() - 1) {
					m_currentFrame = m_textureFrames->GetTotalFrames() - 1;
				}
			}

			m_frameTimer -= frameTime;
		}
	}

	void SpriteAnimationRendererComponent::Draw(const Renderer& renderer) const {
		if (!m_textureFrames) {
			std::cerr << "TextureFrames not available to draw: " << m_textureFrames << std::endl;
			return;
		}

		auto transform = GetOwner()->GetTransform();
		renderer.DrawTexture(
			*m_textureFrames->GetTexture(),
			m_textureFrames->GetFrameRect(m_currentFrame),
			transform);
	}

	void SpriteAnimationRendererComponent::Read(const JSON::value_t& value) {
		RendererComponent::Read(value);

		JSON_READ_MEMBER_REQUIRED(value, "framesPerSecond", m_framesPerSecond);
		JSON_READ_MEMBER(value, "looping", m_looping);

		std::string textureFrames;
		JSON_READ_BY_DATA_REQUIRED(value, textureFrames);

		if (textureFrames.empty()) {
			std::cerr << "Invalid data";
			return;
		}

		m_textureFrames = Resources().Get<TextureFrames>(textureFrames, G_Engine().GetRenderer());
	}
}