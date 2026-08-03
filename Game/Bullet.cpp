#include "Bullet.h"
#include "EngineMath.h"

using namespace ChiefEngine;

void Bullet::Update(float dt, float maxX, float maxY) {
	Vector2 forward{ 1.0f, 0.0f };
	Vector2 velocity = forward.Rotate(m_transform.rotation * DEGREE_TO_RADIAN) * m_speed;

	AddVelocity(velocity);

	Actor::Update(dt, maxX, maxY);
}