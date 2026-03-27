#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_timer.h>
#include <cstdint>
#include <game.hpp>

void Game::run()
{
  Sprite player({
      .x = static_cast<float>(WindowWidth()) / 2.0f,
      .y = static_cast<float>(WindowHeight()) / 2.0f,
      .w = 20.0f,
      .h = 20.0f,
      .r = 255.0f,
      .g = 255.0f,
      .b = 255.0f,
      .a = 255.0f,
  });

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
      case SDL_EVENT_KEY_DOWN:
      {
        if (keycode == SDLK_W)
          player.movement |= 1; // 0000 0001
        if (keycode == SDLK_A)
          player.movement |= 2; // 0000 0010
        if (keycode == SDLK_S)
          player.movement |= 4; // 0000 0100
        if (keycode == SDLK_D)
          player.movement |= 8; // 0000 1000
        break;
      }
      case SDL_EVENT_KEY_UP:
      {
        if (keycode == SDLK_W)
          player.movement &= 14; // 0000 1110
        if (keycode == SDLK_A)
          player.movement &= 13; // 0000 1101
        if (keycode == SDLK_S)
          player.movement &= 11; // 0000 1011
        if (keycode == SDLK_D)
          player.movement &= 7; // 0000 0111
        break;
      }
      }
    }

    player.Update(dt);

    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255); // Set background to black
    if (!SDL_RenderClear(m_Renderer))
    {
      std::cerr << "failed to clear renderer: " << SDL_GetError() << std::endl;
      return;
    }
    DrawSprite(player);

    if (!SDL_RenderPresent(m_Renderer))
    {
      std::cerr << "failed to rendering: " << SDL_GetError() << std::endl;
      return;
    }
  }
};
