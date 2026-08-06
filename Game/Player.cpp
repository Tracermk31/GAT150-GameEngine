#include "Input.h"
#include "Assets.h"
#include "Bullet.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"

using namespace ChiefEngine;

void Player::Update(float dt, float maxX, float maxY) {

    float thrust = 0.0f;
    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +m_speed;
    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + (rotate * dt));

    Vector2 forward{ 1.0f, 0.0f };
    Vector2 velocity = forward.Rotate(m_transform.rotation * DEGREE_TO_RADIAN) * thrust;
    AddVelocity(velocity * dt);

    if (thrust) {
        Particle thrusterFlame;
        Vector2 offset = { -1.5f * m_transform.scale, 0.0f };
        offset = offset.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        thrusterFlame.position = m_transform.position + offset;

        Color colors[3] = { {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.5f, 0.0f} };
        thrusterFlame.color = colors[RandomInt(3)];
        thrusterFlame.lifespan = RandomFloat(0.5f, 1.5f);
        thrusterFlame.velocity = Vector2{ RandomFloat(-30.0f, -100.0f), 0 }.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);

        G_Engine().GetParticleSystem().AddParticle(thrusterFlame);
    }

    //Shoot bullets
    m_shootDelay -= dt;
    if (m_shootDelay <= 0 && G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        m_shootDelay = 0.25f;

        BulletDesc bulletDesc;
        bulletDesc.name = "Bullet";
        bulletDesc.tag = "PlayerBullet";
        bulletDesc.model = Assets::bulletModel;
        bulletDesc.transform = m_transform;
        bulletDesc.transform.scale = m_transform.scale / 4;
        bulletDesc.speed = 200.0f;
        bulletDesc.lifespan = 0.1f;

        m_scene->AddActor(std::move(std::make_unique<Bullet>(bulletDesc)));

        G_Engine().GetAudio().PlaySound("Laser", G_Engine().GetAudio().GetChannel(1));
    }

    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_X)) {
        G_Engine().GetTime().SetTimeScale(0.5f);
    } else {
        G_Engine().GetTime().SetTimeScale(1.0f);
    }

    Actor::Update(dt, G_Engine().GetRenderer().getWindowWidth(), G_Engine().GetRenderer().getWindowHeight());
}

void Player::OnCollision(Actor* other) {
    if (other->GetTag() == "EnemyShip") {
        //G_Engine().GetAudio().PlaySound("Explosion", G_Engine().GetAudio().GetChannel(2));
        BeDestroyed();
        ((SpaceGame*)m_scene->GetGame())->OnPlayerDeath();
    }
}