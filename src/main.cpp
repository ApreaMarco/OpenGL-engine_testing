

#include "main.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alc.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "engine.h"
#include "resource_manager.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

// function declarations
void poll_events();

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

bool windowShouldClose = false;
Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT);

int Main::engine_main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif
    SDL_Window* window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    // SDL_SetWindowResizable(window, SDL_FALSE);
    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // tell stb_image.h to flip loaded texture's on the y-axis
    stbi_set_flip_vertically_on_load(true);

    // OpenAL initialization
    // ---------------------
    ALCdevice *audioDevice;
    ALCcontext *audioContext;
    audioDevice = alcOpenDevice(NULL);
    audioContext = alcCreateContext(audioDevice, nullptr);
    alcMakeContextCurrent(audioContext);

    // ImGui initialization
    // --------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
    io.IniFilename = NULL;
    io.LogFilename = NULL;
    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init();

    // initialize engine
    // ---------------
    engine.Init(window);

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!windowShouldClose)
    {
        // calculate delta time
        // --------------------
        float currentFrame = SDL_GetTicks();
        deltaTime = (currentFrame - lastFrame) * 0.001f;
        lastFrame = currentFrame;

        // manage user input
        // -----------------
        poll_events();
        engine.ProcessInput(deltaTime);

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // update engine state
        // -----------------
        engine.Update(deltaTime);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        engine.Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
    }

    // delete all resources
    // ---------------------------------------------------------
    ResourceManager::Clear();
    if (context) SDL_GL_DeleteContext(context);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return 0;
}

void poll_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {   
        ImGui_ImplSDL2_ProcessEvent(&event);
        engine.ProcessEvent(event);
        if (event.type == SDL_QUIT)
            windowShouldClose = true;
    }
}

