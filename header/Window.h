#pragma once
#include <SDL3/SDL.h>
#include <OpenGL/gl3.h>

class Window {
    public:
        Window(const char* name, int width, int height); //constructor taking in name, window dimensions
        ~Window(); //destructor

        bool isValid() const;
        void swapBuffers() const;

        bool getWindowSize(int& width, int& height) const;
        bool setRelativeMouseMode(bool enabled);


    private:
        SDL_Window* window = nullptr;
        SDL_GLContext context = nullptr;
        bool sdlInitialized = false;
};