#include "pch.h"

#include "Actor.h"
#include "Texture.h"
#include "Renderer.h"
#include "EngineMath.h"

namespace ChiefEngine {
    /// <summary>
    /// Update function that determines the actor's position and whether they are still alive.
    /// </summary>
    /// <param name="dt"> Delta Time for a given Scene.</param>
    /// <param name="maxX">The maximum width of a given Scene.</param>
    /// <param name="maxY">The maximum Height of a given Scene</param>
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

    /// <summary>
    /// Draw function that draws the Actor onto the screen using the renderer
    /// </summary>
    /// <param name="renderer"> The renderer being used to draw</param>
    void Actor::Draw(const Renderer& renderer) const {
        if (m_model) {
            renderer.DrawModel(*m_model, m_transform);
        }
        else if (m_texture) {
            renderer.DrawTexture(*m_texture, m_transform.position.x, m_transform.position.y, m_transform.rotation, m_transform.scale);
        }
    }

    /// <summary>
    /// Gets the radius of an actor. Used for basic collision checks.
    /// </summary>
    /// <returns>The models radius multipled by the Actor's scale and reduced slightly</returns>
    float Actor::GetRadius() const {
        if (m_model) {
            return m_model->GetRadius() * m_transform.scale * 0.9f;
        } else if (m_texture) {
            return m_texture->GetSize().Length() * 0.5f * 0.9f;
        }
        return 0.0f;
    }
}