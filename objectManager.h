#include "drawable.h"
#include <vector>
#include <unordered_map>

/**
 * ObjectManager class: this class contains a vector of all game
 * objects and manages updating and rendering them each frame.
 */
class ObjectManager {
public:
	ObjectManager() : gameObjects(), instanceSets() {}
	~ObjectManager();

	void addObject(Drawable*);
	void initGameObjects(); //generate all objects in the scene
	void updateObjects(Uint32 ticks); //update all objects
	void drawObjects(); //draw all objects

	std::vector<Drawable*>* getInstancesOfType(const std::string&);
private:
	std::vector<Drawable*> gameObjects;
	std::unordered_map<std::string, std::vector<Drawable*>*> instanceSets;
};
