#pragma once
#include <vector>
#include "GameObject.h"

class Scene {
    public:
        Scene() = default;

        vector<GameObject
        void addObject(GameObject object); // Add the object to the Scene
    private:
        vector<GameObject> sceneObjects; //a list that stores all the gameobjects, for which we can access properties
};