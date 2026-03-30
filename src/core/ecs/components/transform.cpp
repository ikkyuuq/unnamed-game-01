#include "transform.hpp"

void ecs::component::Transform::position(glm::vec3 pos)
{
  m_position = pos;
  m_transform_dirty = true;
}

const glm::vec3 &ecs::component::Transform::position() const { return m_position; }

void ecs::component::Transform::rotation(glm::quat rot)
{
  m_rotation = rot;
  m_transform_dirty = true;
}

const glm::quat &ecs::component::Transform::rotation() const { return m_rotation; }

void ecs::component::Transform::scale(glm::vec3 s)
{
  m_scale = s;
  m_transform_dirty = true;
}

const glm::vec3 &ecs::component::Transform::scale() const { return m_scale; }

const glm::mat4 ecs::component::Transform::transform_matrix() const
{
  if (m_transform_dirty)
  {
    m_transform_matrix = glm::translate(glm::mat4(1.0f), m_position) *
                         glm::mat4_cast(m_rotation) * glm::scale(glm::mat4(1.0f), m_scale);
    m_transform_dirty = false;
  }
  return m_transform_matrix;
}
