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

	//Enemy(const ChiefEngine::Transform& transform, float speed) :
	//	Actor{ transform },
	//	m_speed { speed }
	//{}

	//Enemy(const ChiefEngine::Transform& transform, const ChiefEngine::Model& model, float speed) :
	//	Actor{ transform, model },
	//	m_speed{ speed }
	//{}

	void Update(float dt, float maxX, float maxY) override;
	void OnCollision(Actor* other) override;
private:
	float m_speed = 0.0f;
};