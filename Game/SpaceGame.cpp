#include "SpaceGame.h"

#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include <iostream>

using namespace ChiefEngine;

const float FONT_SIZE = 16.0f;

bool SpaceGame::Initialize() {
	Game::Initialize();

	Engine::Get().GetAudio().AddSound("Laser", "audio/laser.wav");
	//Engine::Get().GetAudio().AddSound("BGM", "audio/BackgroundMusic.wav");
	//Engine::Get().GetAudio().setSoundLoop("BGM", true);
	Engine::Get().GetAudio().AddSound("Explosion", "audio/explosion.wav");

	m_scene = new Scene();
	m_scene->SetGame(this);

	m_font = new Font();
	m_font->Load("Fonts/ArcadeNormal.ttf", FONT_SIZE);
	m_titleText = new Text(m_font);
	m_scoreText = new Text(m_font);
	m_livesText = new Text(m_font);
	m_gameOverText = new Text(m_font);
	m_controlsText = new Text(m_font);
	m_pressSpaceText = new Text(m_font);

	m_titleText->Create(Engine::Get().GetRenderer(), "Space Game", {1.0f, 1.0f, 1.0f});
	m_scoreText->Create(Engine::Get().GetRenderer(), "SCORE: " + std::to_string(m_score), {1.0f, 1.0f, 1.0f});
	m_livesText->Create(Engine::Get().GetRenderer(), "LIVES: " + std::to_string(m_lives), {1.0f, 1.0f, 1.0f});
	m_gameOverText->Create(Engine::Get().GetRenderer(), "YOU DIED", {1.0f, 1.0f, 1.0f});
	m_controlsText->Create(Engine::Get().GetRenderer(), "CONTROLS SPACE: SHOOT | X: BULLET TIME | WA: Thrust Forward/Backwards | SD: Rotate Left/Right", {1.0f, 1.0f, 1.0f});
	m_pressSpaceText->Create(Engine::Get().GetRenderer(), "Press Space", {1.0f, 1.0f, 1.0f});
	return true;
}

void SpaceGame::Update(float dt, float maxX, float maxY) {
	switch (m_gameState) {
	case GameState::Title:
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = GameState::StartGame;
		}
		break;
	case GameState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_gameState = GameState::StartLevel;
		break;
	case GameState::StartLevel:
		m_scene->DeleteActors();
		SpawnPlayer(maxX, maxY);
		SpawnEnemy(maxX, maxY);
		m_spawnTimer = 3.0f;
		m_spawnBossTimer = 10.0f;
		m_gameState = GameState::GamePlay;
		break;
	case GameState::GamePlay:
		//Engine::Get().GetAudio().PlaySound("BGM", Engine::Get().GetAudio().GetChannel(2));
		m_spawnTimer -= dt; 
		if (m_spawnTimer <= 0) {
			SpawnEnemy(maxX, maxY);
			m_spawnTimer = 3.0f;
		} 

		m_spawnBossTimer -= dt;
		if (m_spawnBossTimer <= 0) {
			SpawnBoss(maxX, maxY);
			m_spawnBossTimer = 10.0f;
		}
		break;
	case GameState::GameOver:
		m_scene->DeleteActors();
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = GameState::Title;
		}
		break;
	}
	Game::Update(dt, maxX, maxY);
}

void SpaceGame::Draw(ChiefEngine::Renderer& renderer, float maxX, float maxY) {
	switch (m_gameState) {
	case GameState::Title:
		m_titleText->Draw(renderer, maxX/2 - 180 / 2, 100.0f);
		m_controlsText->Draw(renderer, 200.0f, 200.0f);
		m_pressSpaceText->Draw(renderer, maxX/2 - 100, 1000.0f);
		break;
	case GameState::StartGame:
		break;
	case GameState::StartLevel:
		break;
	case GameState::GamePlay:
		m_scoreText->Create(Engine::Get().GetRenderer(), "SCORE: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 40, 40);
		m_livesText->Create(Engine::Get().GetRenderer(), "LIVES: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, 40, 80);
		break;
	case GameState::GameOver:
		m_gameOverText->Draw(renderer, maxX/2 - 100, (maxY - FONT_SIZE)/2);
		m_pressSpaceText->Draw(renderer, maxX / 2 - 100, 1000.0f);
		break;
	}
	Game::Draw(renderer, maxX, maxY);
}

void SpaceGame::SpawnEnemy(float maxX, float maxY) {
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy";
	enemyDesc.tag = "EnemyShip";
	enemyDesc.speed = 1000.0f;
	enemyDesc.damping = 3.0f;
	enemyDesc.transform = Transform{ Vector2{ RandomFloat(0, maxX), RandomFloat(0, maxY)}, 0.0f, 20.0f };
	enemyDesc.model = Assets::enemyModel;

	m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
}

void SpaceGame::SpawnBoss(float maxX, float maxY) {
	EnemyDesc enemyDesc;
	enemyDesc.name = "Boss";
	enemyDesc.tag = "EnemyBoss";
	enemyDesc.speed = 1500.0f;
	enemyDesc.damping = 3.0f;
	enemyDesc.transform = Transform{ Vector2{ RandomFloat(0, maxX), RandomFloat(0, maxY)}, 0.0f, 40.0f };
	enemyDesc.model = Assets::enemyModel;

	m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
}

void SpaceGame::SpawnPlayer(float maxX, float maxY) {
	PlayerDesc playerDesc;
	playerDesc.name = "Player";
	playerDesc.tag = "PlayerShip";
	playerDesc.speed = 2000.0f;
	playerDesc.damping = 3.0f;
	playerDesc.transform = Transform{ Vector2{ maxX / 2.0f, maxY / 2.0f }, 0.0f, 50.0f };
	playerDesc.model = Assets::playerModel;

	m_scene->AddActor(std::move(std::make_unique<Player>(playerDesc)));
}

void SpaceGame::OnPlayerDeath() {
	m_lives--;
	if (m_lives <= 0) {
		m_gameState = GameState::GameOver;
	} else {
		m_gameState = GameState::StartLevel;
	}
}