#include "SDL3_image/SDL_image.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_video.h>
#include <iostream>
#include <ostream>

const char *windowTitle = "I Can't Believe It!";
const int windowWidth = 960;
const int windowHeight = 540;

int main(int argc, char *argv[]) {

  // Init SDL and SubSystems
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) == false) {
    std::cerr << "SDL_INIT_VIDEO Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  };

  SDL_Window *window = SDL_CreateWindow(windowTitle, windowWidth, windowHeight,
                                        SDL_WINDOW_BORDERLESS);
  if (window == nullptr) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == nullptr) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 1;
  }

  char *basePath = SDL_GetCurrentDirectory();
  char *snoopyBmpPath = strcat(basePath, "/assets/snoopy.bmp");

  SDL_Texture *snoopyTexture = IMG_LoadTexture(renderer, snoopyBmpPath);

  SDL_Event e;
  bool wantToQuit = false;

  while (!wantToQuit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        wantToQuit = true;
      }
    }

    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, snoopyTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  // SDL Cleanup
  SDL_DestroyTexture(snoopyTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
