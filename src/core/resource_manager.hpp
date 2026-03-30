#pragma once

#include <game.hpp>
#include <stb_image.h>

#include <SDL3/SDL_render.h>
#include <stdexcept>

typedef enum
{
  TEXTURE = 0,
} ResourceType;

typedef struct
{
  const char *key; // texture: player, enemy, background; shader: player, enemy, background
  void *value;     // pointer to the texture or shader or audio
} ResourceValue;

typedef struct
{
  ResourceType key;     // texture, shader, audio
  ResourceValue *value; // pointer to the resource value
} Resource;

class ResourceManager
{
private:
  Resource *m_resources = nullptr;

  ResourceValue load_texture(const char *name, const char *path);

public:
  void load(ResourceType type, const char *path);

  SDL_Texture *get_texture(const char *name);
};
