#pragma once

#include "JSON.h"

#include <string>

namespace ChiefEngine {
	class Object {
	public:
		Object() = default;
		virtual ~Object() = default;

		inline const std::string& GetName() const { return m_name; }
		inline bool IsActive() const { return m_active; }
		inline void SetActive(bool activeState = true) { m_active = activeState; }

		inline virtual void Read(const JSON::value_t& value) {
			JSON_READ_MEMBER(value, "name", m_name);
			JSON_READ_MEMBER(value, "active", m_active);
		}

	protected:
		inline void SetName(const std::string& name) { m_name = name; }

		std::string m_name = "[DEFAULT]";
		bool m_active = false;
	};
}