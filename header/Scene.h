#pragma once
#include "GameObject.h"
#include <vector>

class Scene {
    public:
        Scene() = default;

        const std::vector<GameObject>& getList() const; // Gets our current list (read only)
        void removeObject(unsigned int index); // Pops the index of the game object
        void addObject(GameObject object); // Add the object to the Scene

        GameObject& getObject(unsigned int index); // Get the game object at the index in array (if it exists)
        void setObject(unsigned int index, GameObject object); // Sets the game object at the index in array (if it exists)

    private:
        std::vector<GameObject> sceneObjects; //a list that stores all the gameobjects, for which we can access properties
};