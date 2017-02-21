#ifndef FRAMEGEN_H
#define FRAMEGEN_H

#include <string>
#include <SDL.h>

const int WIDTH  = 640;
const int HEIGHT = 480;
const std::string USERNAME = "jsavold";
const int unsigned MAX_FRAMES = 822;


class FrameGenerator {
public:
  FrameGenerator(SDL_Renderer* const r, SDL_Window* const win) : 
    rend(r), window(win),
    frameCount(0) 
  {}
  void makeFrame();
  unsigned int getFrameCount() const { return frameCount; }
private:
  SDL_Renderer* const rend;
  SDL_Window* const window;
  unsigned int frameCount;
  FrameGenerator(const FrameGenerator&);
  FrameGenerator& operator=(const FrameGenerator&);
};

#endif
