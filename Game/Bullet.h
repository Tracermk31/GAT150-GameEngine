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

	CLASS_PROTOTYPE(Bullet)

	void Update(float dt, float maxX, float maxY) override;

	void Read(const ChiefEngine::JSON::value_t& value) override;

	inline void SetSpeed(float speed) {
		m_speed = speed;
	}

private:
	float m_speed = 0.0f;
};