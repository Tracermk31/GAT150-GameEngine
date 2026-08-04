#pragma once

#include "Scene.h"

struct PlayerDesc : public ChiefEngine::ActorDesc {
	float speed;
};

class Player : public ChiefEngine::Actor {
public:
	Player() = default;

	Player(PlayerDesc playerDesc) :
		Actor{ playerDesc },
		m_speed { playerDesc.speed }
	{ }

	//Player(const ChiefEngine::Transform& transform, const ChiefEngine::Model& model, float speed) :
	//	Actor{ transform, model },
	//	m_speed{ speed }
	//{ }

	void Update(float dt, float maxX, float maxY) override;
	void OnCollision(Actor* other) override;
private:
	float m_speed = 0.0f;
	float m_shootDelay = 0.0f;
};