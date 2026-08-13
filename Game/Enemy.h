#pragma once

#include "Scene.h"

struct EnemyDesc : public ChiefEngine::ActorDesc {
float speed;
};

class Enemy : public ChiefEngine::Actor {
public:
	Enemy() = default;

	Enemy(EnemyDesc enemyDesc) :
		Actor{ enemyDesc },
		m_speed{ enemyDesc.speed }
	{}

	void Update(float dt, float maxX, float maxY) override;
	void OnCollision(Actor* other) override;

	void Read(const ChiefEngine::JSON::value_t& value) override;
private:
	float m_speed = 0.0f;
};