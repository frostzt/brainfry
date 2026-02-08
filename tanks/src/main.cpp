#include <SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <iostream>

constexpr uint32_t HEIGHT = 800;
constexpr uint32_t WIDTH = 600;

int main() {
  /* initialize sdl */
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    const char *err = SDL_GetError();
    std::cerr << "Tanks failed with fatal error: " << err << std::endl;
    return -1;
  }

  /* create window and renderer */
  SDL_Window *window =
      SDL_CreateWindow("Tanks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_Event e;
  bool quit = false;

  /* main loop */
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {}
    }

    /* clear screen and set to black */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    /* NOTE: core logic starts from here! */

    const SDL_Rect my_tank{0, 0, 10, 10};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &my_tank);

    /* NOTE: core logic ends here! */

    /* update screen */
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
