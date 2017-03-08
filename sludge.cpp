#include "sludge.h"
#include "gamedata.h"
#include "objectManager.h"
#include "viewport.h"
#include <math.h>

Sludge::Sludge() : Sprite("sludge", Vector2f(
	Gamedata::getInstance().getRandInRange(0, 200),
	Gamedata::getInstance().getRandInRange(0, 200))),
	radius(Gamedata::getInstance().getXmlFloat("sludge/radius"))
{ }

Sludge::Sludge(const Vector2f& pos) : Sprite("sludge", pos),
	radius(Gamedata::getInstance().getXmlFloat("sludge/radius"))
{ }

// void Sludge::draw() const {

// }

float clamp(float val, float low, float high) {
	if (val < low) val = low; 
	if (val > high) val = high;
	return val;
}

void Sludge::update(Uint32 ticks) {
	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);

	float gravityConstant = Gamedata::getInstance().getXmlFloat("gravityConstant");
	float dampingConstant = Gamedata::getInstance().getXmlFloat("dampingConstant");
	float maxSpeed = Gamedata::getInstance().getXmlFloat("maxSpeed");

	Vector2f accel;

	//gravity
	float vspeed = getVelocityY();
	if (vspeed < 200.0) accel[1] += gravityConstant;

	//impact bounce
	if (getY() > (getWorldHeight()-100)) {
		float normalForce = (1.0)*pow((getY()-(getWorldHeight()-100)),2);
		accel[1] -= normalForce;
	}

	//other objects
	for (Drawable* d : *ObjectManager::getInstance().getInstancesOfType("sludge")) {
		if (d == this) continue;
		Sludge* sludge = (Sludge*) d;
		float dist = getDistance(sludge);
		float xratio = (getX()-sludge->getX()) / dist;
		float yratio = (getY()-sludge->getY()) / dist;
		if (dist < radius) {
			float magnitude = gravityConstant / sqrt((radius - dist) / radius);
			accel[0] += xratio * magnitude;
			accel[1] += yratio * magnitude;
		}
	}

	//seek mouse
	Vector2f target;
	target[0] = Gamedata::getInstance().getMouseX() + Viewport::getInstance().getX();
	target[1] = Gamedata::getInstance().getMouseY() + Viewport::getInstance().getY();
	float dist = getDistance(target);
	float xratio = (getX()-target[0]) / dist;
	float yratio = (getY()-target[1]) / dist;
	accel[0] -= Gamedata::getInstance().getXmlFloat("sludge/seekSpeed") * xratio;
	accel[1] -= Gamedata::getInstance().getXmlFloat("sludge/seekSpeed") * yratio;

	//damping
	accel = accel - (dampingConstant * getVelocity());

	setVelocity(getVelocity() + accel);
	setVelocityX(clamp(getVelocityX(), -maxSpeed, maxSpeed));
	setVelocityY(clamp(getVelocityY(), -maxSpeed, maxSpeed));
}