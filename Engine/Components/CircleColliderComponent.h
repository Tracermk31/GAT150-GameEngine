#pragma once

#include "ColliderComponent.h"

namespace ChiefEngine {
	class CircleColliderComponent : public ColliderComponent {
	public:
		CLASS_PROTOTYPE(CircleColliderComponent)

		bool CheckCollision(const ColliderComponent& other) override;

		void Read(const JSON::value_t& value) override;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		inline float GetRadius() const { return m_radius; }
	protected:
		float m_radius = 0.0f;
	};
}
