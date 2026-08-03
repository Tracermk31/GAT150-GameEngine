#include "Assets.h"

using namespace ChiefEngine;

namespace Assets {

	Model shipModel = std::vector<Mesh> {
		{{ Vector2{-1.5f, -1.0f,}, Vector2{ 1.5f, 0.0f }, Vector2{-1.5f, 1.0f}, Vector2{-1.5f, -1.0f} } , Color{255.0f, 255.0f, 255.0f} },
		{{ Vector2 {-1.5f, -1.0f}, Vector2 {0.0f, -1.0f}, Vector2 {0.0f, -1.5f}, Vector2 {-1.5f, -1.5f}, Vector2 {-1.5f, -1.0f}}, Color{ 0.0f, 0.0f, 200.0f } },
		{{ Vector2 {-1.5f, 1.0f}, Vector2 {0.0f, 1.0f}, Vector2 {0.0f, 1.5f}, Vector2 {-1.5f, 1.5f}, Vector2 {-1.5f, 1.0f}}, Color{ 0.0f, 0.0f, 200.0f } }
	};

	Mesh playerMesh(
		{
			Vector2{-1.5f, -1.0f,},
			Vector2{ 1.5f, 0.0f },
			Vector2{-1.5f, 1.0f},
			Vector2{-1.5f, -1.0f} },
			Color{ 255.0f, 255.0f, 255.0f }
	);
	//Model playerModel = std::vector<Mesh>{ playerMesh };
	Model playerModel = shipModel;

	Mesh enemyMesh(
		{
			Vector2{-1.5f, -1.0f,},
			Vector2{ 1.5f, 0.0f },
			Vector2{-1.5f, 1.0f},
			Vector2{-1.5f, -1.0f} },
			Color{ 255.0f, 255.0f, 255.0f
		}
	);
	Model enemyModel = std::vector<Mesh>{ enemyMesh };

	Mesh bulletMesh { 
		{
		 Vector2{ -1, -1 },
		 Vector2{ 1, 0 },
		 Vector2{ -1, 1 },
		 Vector2{ -1, -1 },
		},
	Color{ 255.0f, 0.0f, 0.0f }
	};
	Model bulletModel = std::vector<Mesh>{ bulletMesh };
}
