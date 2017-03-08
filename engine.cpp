#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "twoWayMultiSprite.h"
#include "sludge.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
  for (auto& it : sprites) {
    delete it;
  }
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  hills("hills", Gamedata::getInstance().getXmlInt("hills/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(-1),

  makeVideo( false )
{
  sprites.push_back( new Sludge() );
  switchSprite();
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  world.draw();
  hills.draw();
  std::stringstream strm;
  strm << "fps: " << clock.getFps();
  io.writeText(strm.str(), 30, 60);

  for(auto* s : sprites) s->draw();

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto* s : sprites) s->update(ticks);
  world.update();
  hills.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  currentSprite = ++currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if (event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_S] ) {
          clock.toggleSloMo();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture " << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture " << std::endl;
          makeVideo = false;
        }
      }
      if (event.type == SDL_MOUSEMOTION) {
        Gamedata::getInstance().updateMouse(event.motion.x, event.motion.y);
      }
    }
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
