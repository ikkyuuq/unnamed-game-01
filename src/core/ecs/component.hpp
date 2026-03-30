#pragma once

#include <core/ecs/systems/component.hpp>

#include <cstddef>

namespace ecs
{
class Entity;
class Component
{
private:
  Entity *m_owner = nullptr;

public:
  virtual ~Component() = default;

  void owner(Entity *entity);
  const Entity *owner() const;

  template <typename T> static size_t s_get_type_id()
  {
    return sys::ComponentTypeIDSystem::s_get_type_id<T>();
  };

protected:
  virtual void init() {};
  virtual void update(float dt) {};
  virtual void render() {};

  friend class Entity;
};
}; // namespace ecs
