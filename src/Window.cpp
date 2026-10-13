#include "Window.h"

Window::Window(const char* name, int width, int height){
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return;
    }
    sdlInitialized = true;

     // Here's where the SDL Presets go
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow(name, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return;
    }
    context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        SDL_Log("OpenGL context failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        window = nullptr;
        SDL_Quit();
        return;
    }

    SDL_GL_SetSwapInterval(1);
}

Window::~Window(){
    if(window != nullptr){ 
        SDL_DestroyWindow(window);
    }
    if(context != nullptr){
        SDL_GL_DestroyContext(context);
    }
    if(sdlInitialized){
        SDL_Quit();
    }
}

bool Window::isValid() const{
    return (window != nullptr && context != nullptr); //Checks that both window and context are not nullptrs
}

void Window::swapBuffers() const{
    SDL_GL_SwapWindow(window);
}

bool Window::getWindowSize(int& width, int& height) const{
    if(window == nullptr){
        return false;
    }
    return SDL_GetWindowSizeInPixels(window, &width, &height);
}