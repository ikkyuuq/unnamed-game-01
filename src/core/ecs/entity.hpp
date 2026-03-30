#pragma once

#include <component.hpp>

#include <stb_ds.h>

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace ecs
{
class Entity
{
protected:
  typedef struct
  {
    size_t key;
    ecs::Component *value;
  } ComponentHM;

private:
  std::vector<std::unique_ptr<Component>> m_components;
  ComponentHM *m_component_map;

  const char *m_name;
  bool m_is_active;

public:
  explicit Entity(const char *name)
      : m_name(name), m_component_map(nullptr), m_is_active(true) {};
  ~Entity() { hmfree(m_component_map); };

  void name(const char *name);
  const char *name();

  void set_active(bool status);
  bool is_active();

  void init();
  void update(float dt);
  void render();

  template <typename T> T *get_component()
  {
    size_t typeID = Component::s_get_type_id<T>();
    ptrdiff_t index = hmgeti(m_component_map, typeID);
    if (index != -1)
    {
      T *value = m_component_map[index].value;
      return value;
    }
    return nullptr;
  };

  template <typename T, typename... Args> T *add_component(Args &&...args)
  {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

    size_t type_id = Component::s_get_type_id<T>();

    ptrdiff_t index = hmgeti(m_component_map, type_id);
    if (index != -1)
    {
      auto value = m_component_map[type_id].value;
      return static_cast<T *>(value);
    }

    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    component->owner(this);

    T *component_ptr = component.get();
    hmput(m_component_map, type_id, component_ptr);
    m_components.emplace_back(std::move(component));

    return component_ptr;
  };

  template <typename T> bool remove_component()
  {
    size_t type_id = Component::s_get_type_id<T>();
    ptrdiff_t index = hmgeti(m_component_map, type_id);
    if (index != -1)
    {
      auto value = m_component_map[type_id].value;
      hmdel(m_component_map, type_id);
      for (auto it = m_components.begin(); it != m_components.end(); it++)
      {
        if (it->get() == value)
        {
          m_components.erase(it);
          return true;
        }
      }
    }
    return false;
  };
};
}; // namespace ecs
