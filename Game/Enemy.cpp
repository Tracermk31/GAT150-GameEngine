#include "Enemy.h"
#include "Player.h"
#include "Engine.h"
#include "SpaceGame.h"

using namespace ChiefEngine;

void Enemy::Update(float dt, float maxX, float maxY) {
    Vector2 forward{ 1.0f, 0.0f };

    Actor* player = m_scene->GetActorByTag("PlayerCharacter");
    if (player) {
        Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();
        SetRotation(rotation * RADIAN_TO_DEGREE);

        Vector2 velocity = forward.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        AddVelocity(velocity * m_speed * dt);
    }

    Actor::Update(dt, G_Engine().GetRenderer().getWindowWidth(), G_Engine().GetRenderer().getWindowHeight());
}

void Enemy::OnCollision(Actor* other) {
    if (other->GetTag() == "PlayerBullet") {
        G_Engine().GetAudio().PlaySound("Explosion", G_Engine().GetAudio().GetChannel(2));
        BeDestroyed();
        other->BeDestroyed();

        if (this->GetTag() == "EnemyShip") {
            ((SpaceGame*)m_scene->GetGame())->AddPoints(100);
        } else {
            ((SpaceGame*)m_scene->GetGame())->AddPoints(500);
        }

        for (short index = 0; index < 100; index++) {
            Particle shipDebris;
            shipDebris.position = m_transform.position;
            shipDebris.color = { 1.0f, 1.0f, 1.0f };
            shipDebris.lifespan = RandomFloat(0.5f, 2.0f);
            shipDebris.velocity = { RandomFloat(-600.0f, 600.0f), RandomFloat(-600.0f, 600.0f) };
            shipDebris.scale = 0.02f * m_transform.scale;

            G_Engine().GetParticleSystem().AddParticleAsTexture(shipDebris, "Textures/ShipDebris.png", G_Engine().GetRenderer());
        }
    }
}

void Enemy::Read(const JSON::value_t& value) {
    Actor::Read(value);
}