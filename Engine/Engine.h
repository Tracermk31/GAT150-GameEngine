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

#include "Physics\Physics.h"

#include <vector>
#include <fmod.hpp>
#include <iostream>

namespace ChiefEngine {
	class Engine : public Singleton<Engine> {
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize(float screenWidth, float screenHeight);
		void Shutdown();

		void Update();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Time& GetTime() { return m_time; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Input& GetInput() { return m_input; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Renderer& GetRenderer() { return m_renderer; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Audio& GetAudio() { return m_audioSystem; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		ParticleSystem& GetParticleSystem() { return m_particleSystem; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Physics& GetPhysics() { return m_physics; }
	private:
		ParticleSystem m_particleSystem;
		Time m_time;
		Input m_input;
		Renderer m_renderer;
		Audio m_audioSystem;
		Physics m_physics;
	};

	inline Engine& G_Engine() { return Engine::Instance(); }
}