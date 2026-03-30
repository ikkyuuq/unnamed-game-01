#include "entity.hpp"

void ecs::Entity::name(const char *name) { m_name = name; }
const char *ecs::Entity::name() { return m_name; }

void ecs::Entity::set_active(bool status) { m_is_active = status; }
bool ecs::Entity::is_active() { return m_is_active; }

void ecs::Entity::init()
{
  for (auto &component : m_components)
  {
    component->init();
  }
}

void ecs::Entity::update(float dt)
{
  for (auto &component : m_components)
  {
    component->update(dt);
  }
}

void ecs::Entity::render()
{
  for (auto &component : m_components)
  {
    component->render();
  }
}
