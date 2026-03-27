#pragma once

#include <SDL3/SDL.h>

#include <cstdint>
#include <iostream>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;
const SDL_WindowFlags WINDOW_FLAGS = SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS;

class Game
{
private:
  SDL_Window *m_window = nullptr;
  SDL_Renderer *m_renderer = nullptr;
  bool m_is_running = true;

public:
  Game()
  {
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
      std::cerr << "failed to Init SDL: " << SDL_GetError() << std::endl;
      return;
    }

    if (!SDL_CreateWindowAndRenderer("unnamed-game", WIDTH, HEIGHT, WINDOW_FLAGS, &m_window,
                                     &m_renderer))
    {
      std::cerr << "failed to create window and renderer: " << SDL_GetError() << std::endl;
      return;
    }
  };
  ~Game()
  {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  };

  void run();
};
