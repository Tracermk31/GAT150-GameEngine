#pragma once

#include "Object.h"

namespace ChiefEngine {
	class Actor;

	class Component : public Object {
	public:
		CLASS_PROTOTYPE(Component)

		Component() = default;
		virtual ~Component() = default;

		inline Actor* GetOwner() const {
			return m_owner;
		}

		inline void SetOwner(Actor* owner) { m_owner = owner; }

		virtual void Start() {}
		virtual void Destroyed() {}

		virtual void Update(float dt) {}
	protected:
		Actor* m_owner = nullptr;
	};
}