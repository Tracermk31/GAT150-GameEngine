#include "pch.h"

#include "Actor.h"
#include "Engine.h"
#include "Texture.h"
#include "Components/SpriteRendererComponent.h"
#include "EngineMath.h"

namespace ChiefEngine {
    FACTORY_REGISTER(Actor)

    /// <summary>
    /// 
    /// </summary>
    /// <param name="other"></param>
    Actor::Actor(const Actor& other) : 
        Object{ other }
        ,m_tag{ other.m_tag } 
        ,m_damping{ other.m_damping } 
        ,m_lifespan{ other.m_lifespan} 
        ,m_transform{ other.m_transform } {
        for (const auto& component : other.m_components) {
            auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
            AddComponent(move(clone));
        }
    }

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

        for (auto& component : m_components) {
            component->Update(dt);
        }

        m_transform.position += (m_velocity * dt);
        m_velocity *= (1.0f/(1.0f + (m_damping * dt)));
    }

    /// <summary>
    /// Draw function that draws the Actor onto the screen using the renderer
    /// </summary>
    /// <param name="renderer"> The renderer being used to draw</param>
    void Actor::Draw(const Renderer& renderer) const {
        for (auto& component : m_components) {
            auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
            if (rendererComponent) {
                rendererComponent->Draw(renderer);
            }
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    void Actor::Read(const JSON::value_t& value) {
        Object::Read(value);

        if (JSON_HAS_BY_NAME(value, "transform")) {
            m_transform.Read(value["transform"]);
        }

        JSON_READ_MEMBER(value, "tag", m_tag);
        JSON_READ_MEMBER(value, "damping", m_damping);
        JSON_READ_MEMBER(value, "velocity", m_velocity);
        JSON_READ_MEMBER(value, "lifespan", m_lifespan);
        JSON_READ_MEMBER(value, "destroyed", m_destroyed);

        if (JSON_HAS_BY_NAME(value, "components")) {
            for (auto& componentValue : JSON_GET_BY_NAME(value, "components").GetArray()) {
                std::string type;
                JSON_READ_BY_DATA(componentValue, type);

                auto component = Factory::Instance().Create<Component>(type);

                if (component) {
                    component->Read(componentValue);
                    AddComponent(std::move(component));
                }
            }
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="component"></param>
    void Actor::AddComponent(std::unique_ptr<Component> component) {
        component->SetOwner(this);
        m_components.push_back(std::move(component));
    }
}