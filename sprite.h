#ifndef SPRITE__H
#define SPRITE__H
#include <string>
#include "drawable.h"

class Sprite : public Drawable {
public:
  Sprite(const std::string&);
  Sprite(const std::string&, const Vector2f&);
  Sprite(const Sprite&);
  virtual ~Sprite() { } 
  Sprite& operator=(const Sprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual void update(Uint32 ticks);
protected:
  int getWorldWidth() const { return worldWidth; }
  int getWorldHeight() const { return worldHeight; }
  int getFrameWidth() const { return frameWidth; }
  int getFrameHeight() const { return frameHeight; }
private:
  const Frame * frame;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;
  int getDistance(const Sprite*) const;
};
#endif
