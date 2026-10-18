#pragma once

void Input::mouseInput(){
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        camera.processMouseMovement(event.motion.xrel, event.motion.yrel);
    }   
}

void Input::keyInput(){
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