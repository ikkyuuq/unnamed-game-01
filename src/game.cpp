#include <game.hpp>

void Game::run()
{
  while (m_is_running)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        m_is_running = false;
      }

      if (!SDL_RenderClear(m_renderer))
      {
        std::cerr << "failed to clear renderer: " << SDL_GetError() << std::endl;
        return;
      }

      if (!SDL_RenderPresent(m_renderer))
      {
        std::cerr << "failed to rendering: " << SDL_GetError() << std::endl;
        return;
      }
    }
  }
};
