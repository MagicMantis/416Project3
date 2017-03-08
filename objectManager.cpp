#include "objectManager.h"

void ObjectManager::initGameObjects() {
	for (int i = 0; i < 10; i++) {
		addObject( new Sludge() );
	}
}

void ObjectManager::addObject(Drawable* obj) {
	gameObjects.push_back(obj);
	auto search = instanceSets.find(obj->getName());
    if(search != instanceSets.end()) {
        std::cout << "Found " << search->first << " " << search->second << '\n';
        search->second->push_back(obj);
    }
    else {
        std::cout << "Not found\n";
        //search->second;
        instanceSets[obj->getName()] = new std::vector<Drawable*>();
        instanceSets[obj->getName()]->push_back(obj);
    }
}

//update all game objects
void ObjectManager::updateObjects(Uint32 ticks) {
	for ( size_t i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[i]->update(ticks);
	}
}

//draw all objects
void ObjectManager::drawObjects() {
	for ( size_t   i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[i]->draw();
	}
}

ObjectManager::~ObjectManager() {
	for (size_t i = 0; i < gameObjects.size(); i++) {
		delete gameObjects[i];
	}
}

std::vector<Drawable*>* ObjectManager::getInstancesOfType(const std::string& type) {
	return instanceSets[type];
}
