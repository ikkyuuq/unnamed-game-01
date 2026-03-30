#include "resource_manager.hpp"

ResourceValue ResourceManager::load_texture(const char *name, const char *path)
{
  int width, height, channels;
  stbi_uc *image_data = stbi_load(path, &width, &height, &channels, 4);
  stbi_set_flip_vertically_on_load(1);
  SDL_Surface *surface =
      SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, image_data, width * 4);
  if (!surface)
  {
    throw std::runtime_error("Failed to load texture: " + std::string(path));
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::s_get_renderer(), surface);
  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
  SDL_DestroySurface(surface);
  stbi_image_free(image_data);
  return ResourceValue{name, texture};
};

void ResourceManager::load(ResourceType type, const char *path)

{
  switch (type)
  {
  case TEXTURE:
  {
    ResourceValue value = load_texture(path, path);

    // stb_ds hash maps with binary keys require an lvalue (so don't pass
    // enum rvalues directly).
    ResourceType type_key = type;
    ptrdiff_t index = hmgeti(m_resources, type_key);
    if (index == -1)
    {
      // Outer hm: ResourceType -> inner sh(map keyed by ResourceValue.key)
      ResourceValue *inner = nullptr;
      hmput(m_resources, type_key, inner);
      index = hmgeti(m_resources, type_key);
    }

    ResourceValue *inner = m_resources[index].value;
    shput(inner, value.key, value.value);
    m_resources[index].value = inner;
    break;
  }
  }
}

SDL_Texture *ResourceManager::get_texture(const char *name)
{
  ResourceType type_key = TEXTURE;
  ptrdiff_t index = hmgeti(m_resources, type_key);
  if (index == -1)
    return nullptr;

  ResourceValue *inner = m_resources[index].value;
  if (!inner)
    return nullptr;

  ResourceValue *value = shgetp_null(inner, name);
  return value ? static_cast<SDL_Texture *>(value->value) : nullptr;
}
