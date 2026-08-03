#pragma once
#include "Vector2.h"
#include <vector>

namespace ChiefEngine {
	class Input {
	public:
		enum class MouseButton {
			LEFT = 1
			, MIDDLE
			, RIGHT
		};

		bool Initialize();
		void Shutdown();
		void Update();

		bool GetKeyDown(short key) const { return m_keyStates[key]; }
		bool GetPrevKeyDown(short key) const { return m_prevKeyStates[key]; }
		bool GetKeyPressed(short key) const { return (GetKeyDown(key) && !GetPrevKeyDown(key)); }
		bool GetKeyReleased(short key) const { return (!GetKeyDown(key) && GetPrevKeyDown(key)); }

		bool GetButtonDown(MouseButton button) const { return m_buttonStates & GetButtonBit(button); }
		bool GetPrevButtonDown(MouseButton button) const { return m_prevButtonStates & GetButtonBit(button); }
		bool GetButtonPressed(MouseButton button) const { return GetButtonDown(button) && !GetPrevButtonDown(button); }
		bool GetButtonReleased(MouseButton button) const { return !GetButtonDown(button) && GetPrevButtonDown(button); }

		Vector2 GetMousePosition() const { return m_mousePosition; }
	private:
		//Keyboard
		int m_numKeys = 0;
		std::vector<bool> m_keyStates;
		std::vector<bool> m_prevKeyStates;

		//Mouse
		uint32_t m_buttonStates = 0;
		uint32_t m_prevButtonStates = 0;
		Vector2 m_mousePosition{ 0 };

		uint32_t GetButtonBit(MouseButton button) const;
	};
}