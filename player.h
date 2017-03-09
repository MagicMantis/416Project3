#include "twoWayMultiSprite.h"

class Player : public TwoWayMultiSprite {
public:
	Player(const std::string&);
	Player(const Player&);

	virtual void draw() const;
	virtual void update(Uint32 ticks);

	void accelerate(float amount); 
	void jump();
private:
	bool onGround();
};
