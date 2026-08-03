#pragma once

#include "Actor.h"

#include <vector>
#include <string>
#include <memory>

namespace ChiefEngine {
	class Game;

	class Scene {
	private:
		std::vector<std::unique_ptr<Actor>> m_actors;
		std::vector<std::unique_ptr<Actor>> m_pendingActors;

		Game* m_game = nullptr;
	public:
		void AddActor(std::unique_ptr <Actor> actor);
		void DeleteActors();

		void Update(float dt, float maxX, float maxY);
		void UpdateCollisions();
		void Draw(const class Renderer& renderer);

		void SetGame(Game* game) { m_game = game; }
		Game* GetGame() { return m_game; }

		template<typename T = Actor>
		inline T* GetActorByName(const std::string& name) {
			for (auto& actor : m_actors) {
				T* tempActor = dynamic_cast<T*>(actor.get());
				if (tempActor && tempActor->m_name._Equal(name)) {
					return tempActor;
				}
			}
			return nullptr;
		}
	};
}