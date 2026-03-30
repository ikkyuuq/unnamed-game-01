#pragma once

#include "component.hpp"

#include <SDL3/SDL_render.h>

namespace ecs::component
{
class Texture : public ecs::Component
{
private:
  SDL_Texture *m_texture = nullptr;
  SDL_FRect m_src_rect = {};
  SDL_FRect m_dest_rect = {};

public:
  ~Texture() {};

  void texture(SDL_Texture *texture) { m_texture = texture; }
  SDL_Texture *texture() const { return m_texture; }

  void dimension(float w, float h)
  {
    m_dest_rect.w = w;
    m_dest_rect.h = h;
  }
  void position(float x, float y)
  {
    m_dest_rect.x = x;
    m_dest_rect.y = y;
  }

protected:
  void init() override {};
  void update(float dt) override {};
  void render() override;
};
}; // namespace ecs::component
