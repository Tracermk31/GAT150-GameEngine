#pragma once

#include "pch.h"
#include "Vector2.h"
#include "Vector3.h"

#include <vector>

namespace ChiefEngine {
	struct Particle {
		bool active{ false };
		float lifespan{ 1 };

		Vector2 position{ 0.0f, 0.0f };
		Vector2 velocity{ 0.0f, 0.0f };
		Color color{ 0.0f, 0.0f, 0.0f };
	};

	class ParticleSystem {
	public:
		ParticleSystem() = default;

		bool Initialize(size_t poolSize = 1000);
		void Shutdown();

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddParticle(const Particle& particle);

	private:
		Particle* GetFreeParticle();

	private:
		std::vector<Particle> m_particles;
	};
}