

#include "engine.h"
#include "resource_manager.h"
#include "camera.h"
#include "model.h"
#include "point_light.h"
#include "sprite2D.h"
#include "post_processor.h"

#include "imgui.h"
#include <iostream>


Shader shader;
Camera* camera;
Model backpack;
glm::mat4 projection;
PointLight* light;
SpriteRenderer* sprite_renderer;
PostProcessor* post_processor;

enum GameState {
    Active, Paused
};
GameState CurrentState;


Engine::Engine(unsigned int width, unsigned int height) 
    : Width(width), Height(height)
{ 

}

Engine::~Engine()
{

}

void Engine::Init(SDL_Window* window)
{
    // init camera
    SDL_SetRelativeMouseMode(SDL_TRUE); // mouse activating dock is only a very specific windowed problem and can be ignored
    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    projection = glm::perspective(glm::radians(camera->Zoom), (float)this->Width / (float)this->Height, 0.1f, 100.0f);

    // configure shaders
    ResourceManager::LoadShader("resources/shaders/3Dshader.vs", "resources/shaders/lighting.fs", nullptr, "basic");
    ResourceManager::LoadShader("resources/shaders/sprite.vs", "resources/shaders/sprite.fs", nullptr, "sprite");
    ResourceManager::LoadShader("resources/shaders/postprocessing.vs", "resources/shaders/postprocessing.fs", nullptr, "postprocessing");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use();
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    shader = ResourceManager::GetShader("basic");
    Shader sprite_shader = ResourceManager::GetShader("sprite");
    sprite_renderer = new SpriteRenderer(sprite_shader);
    post_processor = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);

    // backpack
    backpack = ResourceManager::LoadModel("resources/objects/backpack/backpack.obj", "backpack");

    // lights
    light = new PointLight(glm::vec3(0.0f, 0.0f, 5.0f));

    // sprite2D test
    Texture2D face = ResourceManager::LoadTexture("resources/textures/awesomeface.png", "face");
    Sprite2D* test_sprite1 = new Sprite2D(sprite_renderer, face, glm::vec2(15.0f), glm::vec2(50.0f));
    test_sprite1->Draw();
    Sprite2D* test_sprite2 = new Sprite2D(sprite_renderer, face, glm::vec2(30.0f), glm::vec2(50.0f));
    test_sprite2->Draw();

    // init context
    CurrentState = Active;
}

void Engine::Update(float deltaTime)
{
    
}

void Engine::ProcessInput(float deltaTime)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        SDL_Event* quitEvent = new SDL_Event();
        quitEvent->type = SDL_QUIT;
        SDL_PushEvent(quitEvent);
    }
    if (state[SDL_SCANCODE_W])
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (state[SDL_SCANCODE_S])
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (state[SDL_SCANCODE_A])
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (state[SDL_SCANCODE_D])
        camera->ProcessKeyboard(RIGHT, deltaTime);
}

void Engine::ProcessEvent(SDL_Event event)
{
    switch (event.type) {
        case SDL_MOUSEMOTION:
            if (CurrentState != Active)
                return;
            int xOffset = event.motion.xrel;
            int yOffset = -event.motion.yrel; // y-coordinates go from bottom to top
            camera->ProcessMouseMovement(xOffset, yOffset);
            break;
    }
}

void Engine::Render()
{
    if (CurrentState == Active) {
        post_processor->BeginRender();
            glEnable(GL_DEPTH_TEST);
            shader.Use();
            shader.SetMatrix4("projection", projection);
            shader.SetMatrix4("view", camera->GetViewMatrix());
            shader.SetVector3f("viewPos", camera->Position);
            shader.SetFloat("shininess", 32.0f);
            PointLight::setAllUniforms(shader);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f));
            shader.SetMatrix4("model", model);
            backpack.Draw(shader);
            glDisable(GL_DEPTH_TEST);
            sprite_renderer->Render();
        post_processor->EndRender();
        post_processor->Render();
    } else if (CurrentState == Paused) {
        post_processor->Render();
    }
}

