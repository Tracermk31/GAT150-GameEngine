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
	{ };

	CLASS_PROTOTYPE(Player)

	void Update(float dt, float maxX, float maxY) override;
	void OnCollision(Actor* other) override;

	void Read(const ChiefEngine::JSON::value_t& value) override;
private:
	float m_speed = 0.0f;
	float m_shootDelay = 0.0f;
};