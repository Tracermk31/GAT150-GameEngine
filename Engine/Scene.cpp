#include "pch.h"

#include "Scene.h"
#include "Renderer.h"

namespace ChiefEngine {
	void Scene::AddActor(std::unique_ptr <Actor> actor) {
		actor->m_scene = this;
		m_pendingActors.push_back(std::move(actor));
	}

	void Scene::Update(float dt, float maxX, float maxY) {
		for (auto& actor : m_actors) {
			actor->Update(dt, maxX, maxY);
		}
		UpdateCollisions();
		std::erase_if(m_actors, [](auto& actor) { return actor->m_destroyed; });

		for (auto& actor : m_pendingActors) {
			m_actors.push_back(std::move(actor));
		}
		m_pendingActors.clear();
	}

	void Scene::Draw(const class Renderer& renderer) {
		for (const auto& actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	void Scene::UpdateCollisions() {
		for (auto& thisActor : m_actors) {
			for (auto& otherActor : m_actors) {
				if (thisActor == otherActor || thisActor->m_destroyed || otherActor->m_destroyed) {
					continue;
				}
				float distance = (thisActor->m_transform.position - otherActor->m_transform.position).Length();
				if (distance <= (thisActor->GetRadius() + otherActor->GetRadius())) {
					thisActor->OnCollision(otherActor.get());
					otherActor->OnCollision(thisActor.get());
				}
			}
		}
	}

	void Scene::DeleteActors() {
		m_actors.clear();
	}
}