#include "pch.h"

#include "Renderer.h"
#include "ParticleSystem.h"

namespace ChiefEngine{
	bool ParticleSystem::Initialize(size_t poolSize) {
		m_particles.resize(poolSize);
		return true;
	}

	void ParticleSystem::Shutdown() {
		m_particles.clear();
	}

	void ParticleSystem::Update(float dt) {
		for (auto& particle : m_particles) {
			if (!particle.active) { 
				continue; 
			}

			particle.lifespan -= dt;

			if (particle.lifespan > 0) {
				particle.position += (particle.velocity * dt);
			} else {
				particle.active = false;
			}
		}
	}

	void ParticleSystem::Draw(Renderer& renderer) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				renderer.SetColorVector(particle.color);
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle& particle) {
		Particle* freeParticle = GetFreeParticle();
		if (freeParticle) {
			*freeParticle = particle;
			freeParticle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle() {
		for (auto& particle : m_particles) {
			if (!particle.active) {
				return &particle;
			}
		}

		return nullptr;
	}
}