#include "objectManager.h"
#include "sludge.h"

ObjectManager& ObjectManager::getInstance() {
  static ObjectManager objectManager;
  return objectManager;
}


void ObjectManager::initObjects() {
	for (int i = 0; i < 100; i++) {
		addObject( new Sludge() );
	}
}

void ObjectManager::addObject(Drawable* obj) {
	gameObjects.push_back(obj);
	auto search = instanceSets.find(obj->getName());
    if(search != instanceSets.end()) {
        search->second->push_back(obj);
    }
    else {
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
void ObjectManager::drawObjects() const {
	for ( size_t   i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[i]->draw();
	}
}

ObjectManager::~ObjectManager() {
	for (auto& it : gameObjects) delete it;
	for (auto& it : instanceSets) delete it.second;
}

std::vector<Drawable*>* ObjectManager::getInstancesOfType(const std::string& type) {
	return instanceSets[type];
}
