#include "Input.h"
#include "Assets.h"
#include "Bullet.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"

using namespace ChiefEngine;

void Player::Update(float dt, float maxX, float maxY) {

    float thrust = 0.0f;
    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_W)) {
        thrust = +m_speed;

        Particle thrusterFlame;

        Vector2 offset = { -20.0f * m_transform.scale, 0.0f };
        offset = offset.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        thrusterFlame.position = m_transform.position + offset;

        thrusterFlame.color = { 1.0f, 0.0f, 0.0f };
        thrusterFlame.lifespan = RandomFloat(0.5f, 1.0f);
        thrusterFlame.velocity = Vector2{ RandomFloat(-100.0f, -30.0f), 0 }.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        thrusterFlame.scale = 0.075f;

        G_Engine().GetParticleSystem().AddParticleAsTexture(thrusterFlame, "Textures/ThrusterFlame.png", G_Engine().GetRenderer());
    }

    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_S)) {
        thrust = -m_speed;

        Particle thrusterFlame;
        Particle thrusterFlameTwo;

        Vector2 offset = { 11.5f * m_transform.scale, -10.0f * m_transform.scale };
        offset = offset.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        thrusterFlame.position = m_transform.position + offset;

        Vector2 offsetTwo = { 11.5f * m_transform.scale, 10.0f * m_transform.scale};
        offsetTwo = offsetTwo.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        thrusterFlameTwo.position = m_transform.position + offsetTwo;

        thrusterFlame.color = { 1.0f, 0.0f, 0.0f };
        thrusterFlameTwo.color = { 1.0f, 0.0f, 0.0f };

        thrusterFlame.lifespan = RandomFloat(0.25f, 0.5f);
        thrusterFlameTwo.lifespan = RandomFloat(0.25f, 0.5f);

        thrusterFlame.velocity = Vector2{ RandomFloat(-100.0f, -30.0f), 0 }.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        thrusterFlameTwo.velocity = Vector2{ RandomFloat(-100.0f, -30.0f), 0 }.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);

        thrusterFlame.scale = 0.0375f;
        thrusterFlameTwo.scale = 0.0375f;

        G_Engine().GetParticleSystem().AddParticleAsTexture(thrusterFlame, "Textures/ThrusterFlame.png", G_Engine().GetRenderer());
        G_Engine().GetParticleSystem().AddParticleAsTexture(thrusterFlameTwo, "Textures/ThrusterFlame.png", G_Engine().GetRenderer());
    }

    float rotate = 0.0f;
    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + (rotate * dt));

    Vector2 forward{ 1.0f, 0.0f };
    Vector2 velocity = forward.Rotate(m_transform.rotation * DEGREE_TO_RADIAN) * thrust;
    AddVelocity(velocity * dt);

    //Shoot bullets
    m_shootDelay -= dt;
    if (m_shootDelay <= 0 && G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        m_shootDelay = 0.25f;

        BulletDesc bulletDesc;
        bulletDesc.name = "Bullet";
        bulletDesc.tag = "PlayerBullet";
        //bulletDesc.model = Assets::bulletModel;
        bulletDesc.texture = Resources().Get<Texture>("Textures/Laser.png", G_Engine().GetRenderer());
        bulletDesc.transform = m_transform;

        Vector2 offset = { 20.0f * m_transform.scale, 0.0f };
        offset = offset.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        bulletDesc.transform.position += offset;

        bulletDesc.transform.scale = m_transform.scale*0.5f;
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
    if (other->GetTag() == "EnemyShip" || other->GetTag() == "EnemyBoss") {
        //G_Engine().GetAudio().PlaySound("Explosion", G_Engine().GetAudio().GetChannel(2));
        BeDestroyed();
        ((SpaceGame*)m_scene->GetGame())->OnPlayerDeath();
    }
}