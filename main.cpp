#define ECS_IMPLEMENTATION
#include <core/ecs/ecs.hpp>
#include <core/resource_manager.hpp>
#include <game.hpp>

std::vector<const char *> texture_paths = {
    "assets/textures/player.png",
};

int main()
{
  Game game;

  ResourceManager resources;
  resources.load(TEXTURE, texture_paths[0]);

  ecs::Entity player("Player");
  auto player_transform = player.add_component<ecs::component::Transform>();
  auto player_texture = player.add_component<ecs::component::Texture>();

  player_texture->texture(resources.get_texture(texture_paths[0]));
  player_texture->dimension(32.0f, 32.0f);
  player_texture->position(game.WindowWidth()/2.0f, game.WindowHeight()/2.0f);

  game.add_entity(&player);

  game.run();

  return 0;
}
