#include "texture.hpp"

#include "game.hpp"

void ecs::component::Texture::render()
{
  if (m_texture)
  {
    const SDL_FRect *src =
        (m_src_rect.w != 0.0f && m_src_rect.h != 0.0f) ? &m_src_rect : nullptr;
    SDL_RenderTexture(Game::s_get_renderer(), m_texture, src, &m_dest_rect);
  }
}
