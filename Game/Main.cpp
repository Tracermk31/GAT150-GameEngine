#include "Enemy.h"
#include "Assets.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"

#include <map>

using namespace ChiefEngine;

float SCREEN_WIDTH = 1920.0f;
float SCREEN_HEIGHT = 1200.0f;

int main() {
    srand((unsigned int)time(nullptr));

    SetWorkingDirectory("Assets");

    // INITIALIZATION
    G_Engine().Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    SpaceGame* spaceGame = new SpaceGame(new Scene);
    spaceGame->Initialize();

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

        float dt = G_Engine().GetTime().getDeltaTime();

        G_Engine().Update();

        spaceGame->Update(dt, SCREEN_WIDTH, SCREEN_HEIGHT);

        // RENDER
        G_Engine().GetRenderer().SetColor(0, 0, 0); // Set render draw color to black
        G_Engine().GetRenderer().Clear(); // Clear the renderer 

        spaceGame->Draw(G_Engine().GetRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
        G_Engine().GetParticleSystem().Draw(G_Engine().GetRenderer());

        G_Engine().GetRenderer().DrawTexture(*Resources().Get<Texture>("Textures/Player.png", G_Engine().GetRenderer()), 30, 30);

        G_Engine().GetRenderer().Present(); // Render the screen
    }
    // SHUTDOWN
    G_Engine().Shutdown();

    return 0;
}