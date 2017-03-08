#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "multisprite.h"

class TwoWayMultiSprite : public MultiSprite {
public:
  TwoWayMultiSprite(const std::string&);
  TwoWayMultiSprite(const TwoWayMultiSprite&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void changeDirection() { facingRight = facingRight ? false : true; }
  void setDirection(bool newDir) { facingRight = newDir; }

protected:
  bool facingRight;
};
#endif  
