#include "PlayerController.h"

#include "Engine.h"

#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(PlayerController)

	void PlayerController::Start() {
		Actor::Start();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		assert(m_physicsComponent);
		m_spriteAnimatorRendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
		assert(m_spriteAnimatorRendererComponent);
	}

	void PlayerController::Update(float dt, float maxX, float maxY) {
		Vector2 velocity = m_physicsComponent->GetVelocity();
		if (G_Engine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			velocity.y = -1000.0f;
		}

		m_physicsComponent->SetVelocity(velocity);
		G_Engine().GetRenderer().SetCamera(m_physicsComponent->GetPosition());

		Actor::Update(dt, maxX, maxY);
	}

	void PlayerController::OnCollision(Actor* other) {

	}

	void PlayerController::Read(const JSON::value_t& value) {
		Actor::Read(value);
	}
}