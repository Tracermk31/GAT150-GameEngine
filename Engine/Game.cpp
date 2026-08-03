#include "pch.h"

#include "Game.h"
#include "Renderer.h"

namespace ChiefEngine {
	void Game::Update(float dt, float maxX, float maxY) {
		m_scene->Update(dt, maxX, maxY);
	}

	void Game::Draw(Renderer& renderer, float maxX, float maxY) {
		m_scene->Draw(renderer);
	}
}