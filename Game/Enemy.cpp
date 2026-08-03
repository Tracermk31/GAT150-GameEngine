#include "Enemy.h"
#include "Player.h"
#include "Engine.h"
#include "SpaceGame.h"

using namespace ChiefEngine;

void Enemy::Update(float dt, float maxX, float maxY) {
    Vector2 forward{ 1.0f, 0.0f };

    Actor* player = m_scene->GetActorByName("Player");
    if (player) {
        Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();
        SetRotation(rotation * RADIAN_TO_DEGREE);

        Vector2 velocity = forward.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        AddVelocity(velocity * m_speed * dt);
    }

    Actor::Update(dt, Engine::Get().GetRenderer().getWindowWidth(), Engine::Get().GetRenderer().getWindowHeight());
}

void Enemy::OnCollision(Actor* other) {
    if (other->GetTag() == "PlayerBullet") {
        Engine::Get().GetAudio().PlaySound("Explosion", Engine::Get().GetAudio().GetChannel(2));
        BeDestroyed();
        other->BeDestroyed();

        if (this->GetTag() == "EnemyShip") {
            ((SpaceGame*)m_scene->GetGame())->AddPoints(100);
        } else {
            ((SpaceGame*)m_scene->GetGame())->AddPoints(500);
        }

        for (short index = 0; index < 100; index++) {
            Particle particle;
            particle.position = m_transform.position;
            particle.color = { 1.0f, 1.0f, 1.0f };
            particle.lifespan = RandomFloat(0.5f, 2.0f);
            particle.velocity = { RandomFloat(-600.0f, 600.0f), RandomFloat(-600.0f, 600.0f) };

            Engine::Get().GetParticleSystem().AddParticle(particle);
        }
    }
}