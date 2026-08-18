#include "pch.h"

#include "Actor.h"
#include "Factory.h"
#include "CircleColliderComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(CircleColliderComponent)

	/// <summary>
	/// 
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool CircleColliderComponent::CheckCollision(const ColliderComponent& other) {
		const CircleColliderComponent* circleCollider = dynamic_cast<const CircleColliderComponent*>(&other);
		if (!circleCollider) {
			return false;
		}
		return (GetOwner()->GetTransform().position.Distance(other.GetOwner()->GetTransform().position) <= (m_radius + circleCollider->GetRadius()));
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	void CircleColliderComponent::Read(const JSON::value_t& value) {
		ColliderComponent::Read(value);

		JSON_READ_MEMBER(value, "radius", m_radius);
	}
}