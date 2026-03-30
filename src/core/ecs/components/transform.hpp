#pragma once

#include "component.hpp"

#include <SDL3/SDL_render.h>

#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ecs::component
{
class Transform : public ecs::Component
{
private:
  glm::vec3 m_position = glm::vec3(0.0f);
  glm::quat m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
  glm::vec3 m_scale = glm::vec3(1.0f);

  mutable glm::mat4 m_transform_matrix = glm::mat4(1.0f);
  mutable bool m_transform_dirty = false;

public:
  ~Transform() {};

  void position(glm::vec3 pos);
  void rotation(glm::quat rot);
  void scale(glm::vec3 s);

  const glm::mat4 transform_matrix() const;
  const glm::vec3 &position() const;
  const glm::quat &rotation() const;
  const glm::vec3 &scale() const;
};
}; // namespace ecs::component
