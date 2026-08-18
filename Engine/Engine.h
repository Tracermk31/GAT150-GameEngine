#pragma once

#include "File.h"
#include "Font.h"
#include "JSON.h"
#include "Text.h"
#include "Actor.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"
#include "Random.h"
#include "Factory.h"
#include "Texture.h"
#include "Renderer.h"
#include "Singleton.h"
#include "EngineMath.h"
#include "EngineTime.h"
#include "EngineStrings.h"
#include "ParticleSystem.h"
#include "ResourceManager.h"

#include <vector>
#include <fmod.hpp>
#include <iostream>

namespace ChiefEngine {
	class Engine : public Singleton<Engine> {
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize(float screenWidth, float screenHeight);
		void Shutdown();

		void Update();

		Time& GetTime() { return m_time; }
		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Audio& GetAudio() { return m_audioSystem; }
		ParticleSystem& GetParticleSystem() { return m_particleSystem; }
	private:
		ParticleSystem m_particleSystem;
		Time m_time;
		Input m_input;
		Renderer m_renderer;
		Audio m_audioSystem;
	};

	inline Engine& G_Engine() { return Engine::Instance(); }
}