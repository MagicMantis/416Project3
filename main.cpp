// To compile and link, need to add link flag in Makefile: -lSDL2_image
// Also need to install libsdl2-image-dev

#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "textureManager.h"
#include "objectManager.h"
//#include "frameGenerator.h"

// Approximately 60 frames per second: 1000
const unsigned int DT = 17u; // ***

void draw(SDL_Renderer* rend, TextureManager& tm, ObjectManager& om) {
  //clear the screen
  SDL_RenderClear(rend);

  //draw background and game objects
  SDL_RenderCopy(rend, tm.getBackgroundTexture(), NULL, NULL);
  om.drawObjects(rend);

  //render results
  SDL_RenderPresent(rend);
}

int main( ) {
  //setup SDL
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = 
    SDL_CreateWindow("The Chase", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  SDL_Renderer *renderer = 
    SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  //initailize neccessary variables and objects
  SDL_Event event;
  const Uint8* keystate;
  int nKeys=-1;
  bool makeVideo = false;
  bool done = false;
  FrameGenerator frameGen(renderer, window);

  //load textures with texture manager
  TextureManager tm;
  tm.initTextures(renderer);

  //initalize game objects through object manager
  ObjectManager om;
  om.initGameObjects(tm);

  //stage is the current step in the animation, counter is frame in current stage
  int stage = 0, counter = 0;

  //frame limiting variables
  unsigned int remainder = 0u; // ***
  unsigned int startTime = SDL_GetTicks();
  unsigned int prevTicks = startTime;
  unsigned int frames = 0u;
  
  while ( !done ) {
    //poll for input
    while ( SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        done = true;
      }
      keystate = SDL_GetKeyboardState(&nKeys);
      if (keystate[SDL_SCANCODE_ESCAPE]) { 
        done = true; 
      }
      if (keystate[SDL_SCANCODE_F4]) { 
        makeVideo = true;
      }
    }

    //calculate time past since last frame
    unsigned int currentTicks = SDL_GetTicks();
    unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

    //if too soon, continue;
    if( elapsedTicks < DT ) continue;
    frames++; //increment frames for frame counter

    //update prevTicks and remainder
    prevTicks = currentTicks;
    remainder = elapsedTicks - DT; // ***

    // Generate a frame:
    if ( makeVideo ) frameGen.makeFrame();

    //update game state to handle different stages of animation
    switch (stage) {
      case 0: if (counter > 180) { stage++; counter = 0; } break;
      case 1: if (counter > 100) { stage++; counter = 0; } break;
      case 2: if (counter > 60) { stage++; counter = 0; } break;
      case 3: if (counter > 100) { stage++; counter = 0; } break;
      case 4: if (counter > 140) { stage++; counter = 0; } break;
      case 5: if (counter > 35) { stage++; counter = 0; } break;
      case 6: if (counter > 75) { stage++; counter = 0; } break;
      case 7: if (counter > 10) { stage++; counter = 0; } break;
      case 8: if (counter > 122) { stage++; counter = 0; } break;
      case 9: done = true; break; //end the game animation completes
    }
    counter++;

    //update objects
    om.updateObjects(stage);
    draw(renderer, tm, om);
  }
  //show framerate after program completes
  unsigned int totalTicks = SDL_GetTicks() - startTime;
  std::cout << "fps: " << frames / (totalTicks * .001) << std::endl;

  //cleanup
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
