#include "tanks/debug.hpp"
#include "tanks/tank.hpp"

namespace entity {

int action_move_tank(const SDL_Event &e) {
  DEBUG_INFO("[ACTION] Action move tank called");

  SDL_assert(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP);
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_RIGHT: {
      DEBUG_INFO("[ACTION] Right Arrow was pressed");
      break;
    }
    case SDLK_LEFT: {
      DEBUG_INFO("[ACTION] Left Arrow was pressed");
      break;
    }
    case SDLK_UP: {
      DEBUG_INFO("[ACTION] Up Arrow was pressed");
      break;
    }
    case SDLK_DOWN: {
      DEBUG_INFO("[ACTION] Down Arrow was pressed");
      break;
    }
    }
  } else if (e.type == SDL_KEYUP) {
    switch (e.key.keysym.sym) {
    case SDLK_RIGHT: {
      DEBUG_INFO("[ACTION] Right Arrow was released");
      break;
    }
    case SDLK_LEFT: {
      DEBUG_INFO("[ACTION] Left Arrow was released");
      break;
    }
    case SDLK_UP: {
      DEBUG_INFO("[ACTION] Up Arrow was released");
      break;
    }
    case SDLK_DOWN: {
      DEBUG_INFO("[ACTION] Down Arrow was released");
      break;
    }
    }
  }

  return 0;
}

} // namespace entity
