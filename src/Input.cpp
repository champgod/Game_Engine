#include "Input.h"
#include "Camera.h"
#include <SDL3/SDL.h>

bool Input::processEvent(Camera& camera){
    SDL_Event event;
    bool running = true;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
            running = false;
        }
        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            camera.processMouseMovement(event.motion.xrel, event.motion.yrel);
        }   
    } 

    return running;
}

void Input::updateKeyInput(Camera& camera, float deltaTime){
    const bool* keys = SDL_GetKeyboardState(nullptr);

     if (keys[SDL_SCANCODE_W]) {
        camera.move(MovementDirection::Forward, deltaTime);
    }
    if (keys[SDL_SCANCODE_S]) {
        camera.move(MovementDirection::Backward, deltaTime);
    }
    if (keys[SDL_SCANCODE_A]) {
        camera.move(MovementDirection::Left, deltaTime);
    }
    if (keys[SDL_SCANCODE_D]) {
        camera.move(MovementDirection::Right, deltaTime);
    }
    if (keys[SDL_SCANCODE_R]){
        camera.reset();
    }
    if (keys[SDL_SCANCODE_L]){
        SDL_Log("New position saved!");
        camera.save();
    }
}