#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>

#include <cstdint>
#include <iostream>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;
const SDL_WindowFlags WINDOW_FLAGS = SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS;

class Sprite
{
private:
  glm::vec2 m_Location;
  glm::quat m_Rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
  glm::vec2 m_Size;

  glm::vec4 m_Color;

public:
  uint8_t movement = 0b00000000; // 0000 0000
  float speed = 220.0f;

  struct SpriteProperties
  {
    float x, y;
    float w, h;
    float r, g, b, a;
  };
  Sprite(SpriteProperties props)
  {
    m_Location = glm::vec2(props.x, props.y);
    m_Size = glm::vec2(props.w, props.h);
    m_Color = glm::vec4(props.r, props.g, props.b, props.a);
  };
  ~Sprite() {};

  void Update(float dt)
  {
    glm::float32 dirX = (movement & 8 ? 1.0f : 0.0f) - (movement & 2 ? 1.0f : 0.0f);
    glm::float32 dirY = (movement & 4 ? 1.0f : 0.0f) - (movement & 1 ? 1.0f : 0.0f);

    glm::vec2 dir = glm::vec2(dirX, dirY);
    if (glm::length(dir) > 0.0f) dir = glm::normalize(dir);

    m_Location += dir * speed * dt;
  };

  const glm::vec2 *Location() const { return &m_Location; };
  const glm::vec2 *Size() const { return &m_Size; };
  const glm::vec4 *Color() const { return &m_Color; };
};

class GameState
{
private:
public:
  GameState();
  ~GameState();
};

class Game
{
private:
  SDL_Window *m_Window = nullptr;
  SDL_Renderer *m_Renderer = nullptr;
  bool m_IsRunning = true;

public:
  Game()
  {
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
      std::cerr << "failed to Init SDL: " << SDL_GetError() << std::endl;
      return;
    }

    if (!SDL_CreateWindowAndRenderer("unnamed-game", WIDTH, HEIGHT, WINDOW_FLAGS, &m_Window,
                                     &m_Renderer))
    {
      std::cerr << "failed to create window and renderer: " << SDL_GetError() << std::endl;
      return;
    }
  };
  ~Game()
  {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
  };

  int WindowWidth()
  {
    int width = 0;
    SDL_GetWindowSize(m_Window, &width, nullptr);
    return width;
  };

  int WindowHeight()
  {
    int height = 0;
    SDL_GetWindowSize(m_Window, nullptr, &height);
    return height;
  };
  void run();

  void DrawSprite(Sprite sprite)
  {
    auto location = sprite.Location();
    auto size = sprite.Size();
    auto color = sprite.Color();

    SDL_FRect rect = {.x = location->x, .y = location->y, .w = size->x, .h = size->y};
    SDL_SetRenderDrawColorFloat(m_Renderer, color->r, color->g, color->b, color->a);
    SDL_RenderFillRect(m_Renderer, &rect);
  };
};
