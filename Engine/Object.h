#pragma once

#include <string>

namespace ChiefEngine {
	class Object {
	public:
		Object() = default;
		virtual ~Object() = default;

		inline const std::string& GetName() const { return m_name; }
		inline bool IsActive() const { return m_active; }
		inline void SetActive(bool activeState = true) { m_active = activeState; }
	protected:
		inline void SetName(const std::string& name) { m_name = name; }

		std::string m_name;
		bool m_active = false;
	};
}