

#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <SDL2/SDL.h>

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Engine
{
public:
    // game state
    unsigned int Width, Height;
    // constructor/destructor
    Engine(unsigned int width, unsigned int height);
    ~Engine();
    // initialize game state (load all shaders/textures/levels)
    void Init(SDL_Window* window);
    // game loop
    void ProcessInput(float deltaTime);
    void ProcessEvent(SDL_Event event);
    void Update(float deltaTime);
    void Render();
};

#endif

