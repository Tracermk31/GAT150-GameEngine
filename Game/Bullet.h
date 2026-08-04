#pragma once

#include "Scene.h"

struct BulletDesc : public ChiefEngine::ActorDesc {
	float speed;
};

class Bullet : public ChiefEngine::Actor {
public:
	Bullet() = default;

	Bullet(BulletDesc BulletDesc) :
		Actor{ BulletDesc },
		m_speed{ BulletDesc.speed }
	{}

	//Bullet(const ChiefEngine::Transform& transform, float speed) :
	//	Actor{ transform },
	//	m_speed{ speed }
	//{}

	//Bullet(const ChiefEngine::Transform& transform, const ChiefEngine::Model& model, float speed) :
	//	Actor{ transform, model },
	//	m_speed{ speed }
	//{}

	void Update(float dt, float maxX, float maxY) override;
private:
	float m_speed = 0.0f;
};