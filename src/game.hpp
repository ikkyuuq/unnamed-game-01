#pragma once

#define ECS_IMPLEMENTATION
#include "ecs.hpp"
#include <stb_ds.h>
#include <stb_image.h>

#include <cassert>
#include <cstdint>
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_surface.h>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;
const SDL_WindowFlags WINDOW_FLAGS = SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS;

class Game
{
private:
  static SDL_Window *m_window;
  static SDL_Renderer *m_renderer;
  bool m_IsRunning = true;

  std::vector<ecs::Entity *> m_entities;

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

  static SDL_Window *s_get_window() { return m_window; }
  static SDL_Renderer *s_get_renderer() { return m_renderer; }

  int WindowWidth()
  {
    int width = 0;
    SDL_GetWindowSize(m_window, &width, nullptr);
    return width;
  };

  int WindowHeight()
  {
    int height = 0;
    SDL_GetWindowSize(m_window, nullptr, &height);
    return height;
  };
  void run();

  void add_entity(ecs::Entity *ent) { m_entities.emplace_back(ent); };
};

