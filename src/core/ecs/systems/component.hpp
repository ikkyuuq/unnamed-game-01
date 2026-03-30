#pragma once

#include <cstddef>

namespace ecs::sys
{
class ComponentTypeIDSystem
{
private:
  static size_t m_type_id;

public:
  virtual ~ComponentTypeIDSystem() = default;

  template <typename T> static size_t s_get_type_id()
  {
    size_t type_id = m_type_id++;
    return type_id;
  };
};
}; // namespace ecs::sys
