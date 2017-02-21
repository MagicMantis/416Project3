#include "objectManager.h"

void ObjectManager::initGameObjects(TextureManager& tm) {
	for (int i = 0; i < rain_count*2; i++) {
		gameObjects.push_back(new Rain(i*(WIDTH/rain_count), (rand()%HEIGHT), rand()%3+3, HEIGHT, 5));
	}

	//create buildings
	gameObjects.push_back(new Building(400,250,.7,tm.getTexture("building1")));
	gameObjects.push_back(new Building(670,200,.9,tm.getTexture("building2")));
	gameObjects.push_back(new Building(1000,250,.8,tm.getTexture("building1")));
	gameObjects.push_back(new Building(1100,370,.5,tm.getTexture("building2")));
	gameObjects.push_back(new Building(1100,200,.5,tm.getTexture("building2")));

	//create back ground rain drops
	for (int i = 0; i < rain_count; i++) {
		gameObjects.push_back(new Rain(i*(WIDTH/rain_count), (rand()%HEIGHT), rand()%3+6, HEIGHT, 4));
	}

	//create rooftop
	gameObjects.push_back(new Building(1250,100,1,tm.getTexture("rooftop")));

	//create characters
	gameObjects.push_back(new Detective(1400,370,tm.getTexture("detective")));
	gameObjects.push_back(new Criminal(1650,370,tm.getTexture("criminal")));

	//create raindrops
	for (int i = 0; i < rain_count; i++) {
		gameObjects.push_back(new Rain(i*(WIDTH/rain_count), (rand()%HEIGHT), rand()%2+9, HEIGHT, 4));
	}

	//create text and lightning effects
	gameObjects.push_back(new StageObject(0,0,500,100,1,tm.getTexture("dtext")));
	gameObjects.push_back(new StageObject(0,0,500,100,3,tm.getTexture("ctext")));
	gameObjects.push_back(new Lightning(300,-70,300,300,5,tm.getTexture("lightning")));

	//create fadeout object
	gameObjects.push_back(new FadeOut(0,0,640,480,8));
}

//update all game objects
void ObjectManager::updateObjects(int stage) {
	for ( size_t i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[i]->update(stage);
	}
}

//draw all objects
void ObjectManager::drawObjects(SDL_Renderer* rend) {
	for ( size_t   i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[i]->draw(rend);
	}
}

ObjectManager::~ObjectManager() {
	for (size_t i = 0; i < gameObjects.size(); i++) {
		delete gameObjects[i];
	}
}
