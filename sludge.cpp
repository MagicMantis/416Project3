#include "sludge.h"
#include "gamedata.h"
#include <math.h>

Sludge::Sludge() : Sprite("sludge", Vector2f(
	Gamedata::getInstance().getRandInRange(0, 200),
	Gamedata::getInstance().getRandInRange(0, 200)))
{ }

Sludge::Sludge(const Vector2f& pos) : Sprite("sludge", pos)
{ }

// void Sludge::draw() const {

// }

void Sludge::update(Uint32 ticks) {
	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);

	float gravityConstant = 10.0;
	float dampingConstant = 0.05;

	//gravity
	float vspeed = getVelocityY();
	float accel = 0.0;
	if (vspeed < 200.0) accel += gravityConstant;

	//impact bounce
	if (getY() > (getWorldHeight()-100)) {
		float normalForce = (1.0)*pow((getY()-(getWorldHeight()-100)),2);
		accel -= normalForce;
	}

	//other objects

	//damping
	accel -= dampingConstant * getVelocityY();

	setVelocityY(getVelocityY() + accel);
}