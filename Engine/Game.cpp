#include "pch.h"

#include "Game.h"
#include "Renderer.h"

namespace ChiefEngine {
	/// <summary>
	/// 
	/// </summary>
	/// <param name="dt"></param>
	/// <param name="maxX"></param>
	/// <param name="maxY"></param>
	void Game::Update(float dt, float maxX, float maxY) {
		m_scene->Update(dt, maxX, maxY);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="maxX"></param>
	/// <param name="maxY"></param>
	void Game::Draw(Renderer& renderer, float maxX, float maxY) {
		m_scene->Draw(renderer);
	}
}