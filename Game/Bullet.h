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

	void Update(float dt, float maxX, float maxY) override;

	void Read(const ChiefEngine::JSON::value_t& value) override;
private:
	float m_speed = 0.0f;
};