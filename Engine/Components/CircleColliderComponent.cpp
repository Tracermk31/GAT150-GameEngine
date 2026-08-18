#include "pch.h"

#include "Actor.h"
#include "Factory.h"
#include "CircleColliderComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(CircleColliderComponent)

	bool CircleColliderComponent::CheckCollision(const ColliderComponent& other) {
		const CircleColliderComponent* circleCollider = dynamic_cast<const CircleColliderComponent*>(&other);
		if (!circleCollider) {
			return false;
		}
		return (GetOwner()->GetTransform().position.Distance(other.GetOwner()->GetTransform().position) <= (m_radius + circleCollider->GetRadius()));
	}

	void CircleColliderComponent::Read(const JSON::value_t& value) {
		ColliderComponent::Read(value);

		JSON_READ_MEMBER(value, "radius", m_radius);
	}
}