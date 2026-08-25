#pragma once

#include "PhysicsComponent.h"

namespace ChiefEngine {
	class RigidBodyPhysicsComponent : public PhysicsComponent {
	public:
		CLASS_PROTOTYPE(RigidBodyPhysicsComponent)


		virtual void ApplyForce(const Vector2& force);
		virtual void SetVelocity(const Vector2& velocity);
		virtual Vector2 GetVelocity();

		virtual void ApplyTorque(float torque);
		virtual void SetAngularVelocity(float angularVelocity);
		virtual float GetAngularVelocity() const;

		virtual void SetPosition(const Vector2& position);
		virtual Vector2 GetPosition() const;

		void Update(float dt);
		void Read(const JSON::value_t& value) override;
	private:
		Vector2 m_acceleration{ 0.0f };
		float m_angularAcceleration{ 0.0f };

		Vector2 m_velocity{ 0.0f };
		float m_angularVelocity{ 0.0f };
	};
}