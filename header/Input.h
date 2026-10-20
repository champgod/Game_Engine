#pragma once

#include "Camera.h"

class Input{
    public:
        bool processEvent(Camera& camera);
        void updateKeyInput(Camera& camera, float deltaTime);
};