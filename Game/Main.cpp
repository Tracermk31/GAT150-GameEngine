#include "Enemy.h"
#include "Assets.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"

#include <map>
#include <fstream>

using namespace ChiefEngine;

float SCREEN_WIDTH = 1920.0f;
float SCREEN_HEIGHT = 1200.0f;

class Animal {
public:
    virtual void Speak() { std::cout << "noise\n"; }
};

class Cat : public Animal {
    void Speak() override { std::cout << "meow\n"; }
};

class Dog : public Animal {
    void Speak() override { std::cout << "woof\n"; }
};

class Bird : public Animal {
    void Speak() override { std::cout << "caw\n"; }
};

int main() {
    //Factory::Instance().Register<Actor>("Actor");
    //auto actor = Factory::Instance().Create("Actor");

    SeedRandom((unsigned int)time(nullptr));

    SetWorkingDirectory("Assets");

    std::string name;
    int age;
    float speed;
    bool isAwake;
    Vector2 position;
    Vector3 color;

    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("data/data.json", buffer)) {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (JSON::Load("data/data.json", document)) {
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
        }
    }

    return 0;

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

        G_Engine().GetRenderer().Present(); // Render the screen
    }
    // SHUTDOWN
    G_Engine().Shutdown();

    return 0;
}