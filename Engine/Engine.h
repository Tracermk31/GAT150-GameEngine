#pragma once

#include "pch.h"
#include "File.h"
#include "Audio.h"
#include "Actor.h"
#include "Renderer.h"
#include "Random.h"
#include "Font.h"
#include "Text.h"
#include "Texture.h"
#include "Input.h"
#include "EngineTime.h"
#include "EngineMath.h"
#include "ParticleSystem.h"
#include "Scene.h"

#include <fmod.hpp>
#include <vector>
#include <iostream>

namespace ChiefEngine {
	class Engine {
	public:
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
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
		Engine() = default;

		ParticleSystem m_particleSystem;
		Time m_time;
		Input m_input;
		Renderer m_renderer;
		Audio m_audioSystem;
	};
}