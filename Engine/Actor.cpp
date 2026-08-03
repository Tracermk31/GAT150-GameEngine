#include "pch.h"

#include "Actor.h"
#include "EngineMath.h"
#include "Renderer.h"

namespace ChiefEngine {
    void Actor::Update(float dt, float maxX, float maxY) {
        if (m_lifespan > 0.0f) {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
        }

        m_transform.position += (m_velocity * dt);
        m_velocity *= (1.0f/(1.0f + (m_damping * dt)));

        Wrap(0.0f, maxX, m_transform.position.x);
        Wrap(0.0f, maxY, m_transform.position.y);
    }

    void Actor::Draw(const Renderer& renderer) const {
        renderer.DrawModel(m_model, m_transform);
    }

    float Actor::GetRadius() const {
        return m_model.GetRadius() * m_transform.scale * 0.9f;
    }
}