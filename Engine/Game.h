#pragma once

#include "Scene.h"

namespace ChiefEngine {
	class Game {
	public:
		Game() = default;
		Game(Scene* scene) {
			m_scene = scene;
			m_scene->SetGame(this);
		}

		virtual bool Initialize() { return false; }
		virtual void Shutdown() const {}

		virtual void Update(float dt, float maxX, float maxY);
		virtual void Draw(class Renderer& renderer, float maxX, float maxY) ;

		void SetScene(Scene* scene) { m_scene = scene; }
	protected:
		Scene* m_scene = nullptr;
	private:
	};
}