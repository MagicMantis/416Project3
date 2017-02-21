#include "gameObject.h"
#include "rain.h"
#include "building.h"
#include "texture.h"
#include "detective.h"
#include "criminal.h"
#include "stageObject.h"
#include "lightning.h"
#include "fadeout.h"
#include "textureManager.h"
#include <vector>

const int rain_count = 200;

/**
 * ObjectManager class: this class contains a vector of all game
 * objects and manages updating and rendering them each frame.
 */
class ObjectManager {
public:
	ObjectManager() : gameObjects() {}
	~ObjectManager();

	void initGameObjects(TextureManager& tm); //generate all objects in the scene
	void updateObjects(int stage); //update all objects
	void drawObjects(SDL_Renderer* rend); //draw all objects
private:
	std::vector<GameObject*> gameObjects;
};
