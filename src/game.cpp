#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_timer.h>
#include <cstdint>
#include <game.hpp>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/geometric.hpp>

SDL_Window *Game::m_window = nullptr;
SDL_Renderer *Game::m_renderer = nullptr;

void Game::run()
{
  uint64_t past = SDL_GetPerformanceCounter();
  while (m_IsRunning)
  {
    uint64_t now = SDL_GetPerformanceCounter();
    float dt =
        static_cast<float>(now - past) / static_cast<float>(SDL_GetPerformanceFrequency());
    past = now;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      SDL_Keycode keycode = event.key.key;
      switch (event.type)
      {
      case SDL_EVENT_QUIT:
        m_IsRunning = false;
        break;
      }
    }

    for (auto &entity : m_entities)
    {
      entity->update(dt);
    }

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // Set background to black
    if (!SDL_RenderClear(m_renderer))
    {
      std::cerr << "failed to clear renderer: " << SDL_GetError() << std::endl;
      return;
    }

    for (auto &entity : m_entities)
    {
      entity->render();
    }

    if (!SDL_RenderPresent(m_renderer))
    {
      std::cerr << "failed to rendering: " << SDL_GetError() << std::endl;
      return;
    }
  }
};
