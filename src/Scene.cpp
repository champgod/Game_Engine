#include "Scene.h"

const std::vector<GameObject>& Scene::getList() const{
    return sceneObjects;
}

void Scene::removeObject(unsigned int index) {
    if (index < sceneObjects.size()) {
        sceneObjects.erase(sceneObjects.begin() + index);
    }
}

void Scene::addObject(GameObject object) {
    sceneObjects.push_back(object);
}

GameObject& Scene::getObject(unsigned int index){
    return sceneObjects.at(index);
}

void Scene::setObject(unsigned int index, GameObject object) {
    if (index < sceneObjects.size()){
        sceneObjects.at(index) = object;
    }
}