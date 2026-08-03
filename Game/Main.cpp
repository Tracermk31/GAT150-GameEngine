#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"

#include <map>

using namespace ChiefEngine;

float SCREEN_WIDTH = 1920.0f;
float SCREEN_HEIGHT = 1200.0f;

class Object {
public: 
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }
    Object(const Object& object) { std::cout << "copystructor\n"; }
    Object& operator = (const Object& object) { std::cout << "assignment\n"; return *this; }
};

int main() {
    srand((unsigned int)time(nullptr));

    SetWorkingDirectory("Assets");
    // INITIALIZATION
    Engine::Get().Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    SpaceGame* spaceGame = new SpaceGame(new Scene);
    spaceGame->Initialize();

    std::vector<Vector2> points;

    // MAIN LOOP
    SDL_Event event;
    bool running = true;
    while (running) {

        // UPDATE
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                running = false;
            }
        }

        float dt = Engine::Get().GetTime().getDeltaTime();

        Engine::Get().Update();

        spaceGame->Update(dt, SCREEN_WIDTH, SCREEN_HEIGHT);

        // RENDER
        Engine::Get().GetRenderer().SetColor(0, 0, 0); // Set render draw color to black
        Engine::Get().GetRenderer().Clear(); // Clear the renderer 

        spaceGame->Draw(Engine::Get().GetRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
        Engine::Get().GetParticleSystem().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present(); // Render the screen
    }
    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}