#include "pch.h"

#include "Scene.h"
#include "Factory.h"
#include "Renderer.h"
#include "Components/ColliderComponent.h"

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

	void Scene::Draw(const Renderer& renderer) {
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
				auto thisCollider = thisActor->GetComponent<ColliderComponent>();
				auto otherCollider = otherActor->GetComponent<ColliderComponent>();

				if (!thisCollider || !otherCollider) {
					continue;
				}

				if (thisCollider->CheckCollision(*otherCollider)) {
					thisActor->OnCollision(otherActor.get());
					otherActor->OnCollision(thisActor.get());
				}
			}
		}
	}

	void Scene::DeleteActors() {
		m_actors.clear();
	}

	bool Scene::Load(const std::string& sceneName) {
		JSON::document_t document;
		if (JSON::Load(sceneName, document)) {
			if (JSON_HAS_BY_NAME(document, "actors")) {
				for (auto& actorValue : JSON_GET_BY_NAME(document, "actors").GetArray()) {
					std::string type;	
					JSON_READ_BY_DATA(actorValue, type);

					auto actor = Factory::Instance().Create<Actor>(type);
					actor->Read(actorValue);

					bool prototype = false;
					JSON_READ_BY_DATA(actorValue, prototype);

					if (prototype) {
						std::string name;
						JSON_READ_BY_DATA(actorValue, name);
						Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
					} else {
						AddActor(std::move(actor));
					}
				}
			}
			return true;
		} else {
			return false;
		}
	}
}