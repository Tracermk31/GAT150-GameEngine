#pragma once

#include "Model.h"
#include "Object.h"
#include "Resource.h"
#include "Transform.h"

#include <memory>
#include <string>

namespace ChiefEngine {
    class Scene;
    class Texture;

    /// <summary>
    /// Struct used to contain the information to build an Actor.
    /// </summary>
    struct ActorDesc {
        std::string name;
        std::string tag;
        Transform transform;
        Vector2 velocity = 0.0f;
        float damping = 0.0f;
        float lifespan = -1.0f;
        resource_t<Model> model;
        resource_t<Texture> texture;
    };

    /// <summary>
    /// Parent class for all actors inside of a Scene.
    /// </summary>
    class Actor : public Object {
    public:
        /// <summary>
        /// Default constructor for the Actor class.
        /// </summary>
        Actor() = default;

        /// <summary>
        /// Utilizes the predefined ActorDesc struct to assign all necessary variables to create an Actor
        /// </summary>
        /// <param name="actorDesc"> Predefined struct containing all info to create an Actor</param>
        Actor(const ActorDesc& actorDesc) :
            //SetName(actorDesc.name),
            m_name{ actorDesc.name },
            m_tag{ actorDesc.tag },
            m_transform{ actorDesc.transform },
            m_velocity{ actorDesc.velocity },
            m_damping{ actorDesc.damping },
            m_lifespan{ actorDesc.lifespan },
            m_model{ actorDesc.model },
            m_texture { actorDesc.texture}
        { };

        virtual void Update(float dt, float maxY, float maxX);
        virtual void Draw(const class Renderer& renderer) const;

        virtual void OnCollision(Actor* other) {}

        float GetRadius() const;

        inline const Transform& GetTransform() const { return this->m_transform; }
        void SetPosition(const Vector2& position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.scale = scale; }

        void BeDestroyed() { m_destroyed = true; }

        inline const Vector2& GetVelocity() const { return m_velocity; }
        void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }
        void AddVelocity(const Vector2& velocity) { m_velocity += velocity; }

        std::string GetTag() { return m_tag; }
        Scene* GetScene() { return m_scene; }

        friend Scene;
    protected:
        std::string m_name;
        std::string m_tag;
        Transform m_transform;

        Vector2 m_velocity{ 0.0f };
        float m_damping{ 0.0f };
        float m_lifespan{ -1.0f };
        bool m_destroyed{ false };

        resource_t<Model> m_model;
        resource_t<Texture> m_texture;

        Scene* m_scene{ nullptr };
    };
}