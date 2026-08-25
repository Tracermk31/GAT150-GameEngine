#include "pch.h"

#include "PhysicsComponent.h"

namespace ChiefEngine {
	void PhysicsComponent::Read(const JSON::value_t& value) {
		Component::Read(value);

		JSON_READ_MEMBER(value, "mass", m_mass);
		JSON_READ_MEMBER(value, "damping", m_damping);
		JSON_READ_MEMBER(value, "angular_damping", m_angularDamping);
		JSON_READ_MEMBER(value, "gravity_scale", m_gravityScale);
	}
}

