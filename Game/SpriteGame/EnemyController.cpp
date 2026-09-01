#include "EnemyController.h"

#include "Engine.h"

#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(EnemyController)

	void EnemyController::Start() {
		Actor::Start();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		assert(m_physicsComponent);
		m_spriteAnimatorRendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
		assert(m_spriteAnimatorRendererComponent);
	}

	void EnemyController::Update(float dt, float maxX, float maxY) {
		float dir = 0.0f;
		auto player = m_scene->GetActorByName("PlayerPrototype");
		if (player) {
			Vector2 position = GetTransform().position;
			Vector2 playerPosition = player->GetTransform().position;

			if (playerPosition.x < position.x) {
				dir = -1.0f;
			} else {
				dir = 1.0f;
			}
		}
		Actor::Update(dt, maxX, maxY);
	}

	void EnemyController::OnCollision(Actor* other) {

	}

	void EnemyController::Read(const JSON::value_t& value) {
		Actor::Read(value);
	}
}