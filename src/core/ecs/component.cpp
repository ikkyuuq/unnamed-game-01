#include "component.hpp"


void ecs::Component::owner(ecs::Entity *entity) { m_owner = entity; }
const ecs::Entity *ecs::Component::owner() const { return m_owner; }
