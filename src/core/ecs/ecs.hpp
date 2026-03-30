#pragma once

#ifdef ECS_IMPLEMENTATION
#include <component.hpp>
#include <entity.hpp>
#include <systems/component.hpp>
#include <systems/event.hpp>
#include <texture.hpp>
#include <transform.hpp>
#endif

namespace ecs
{
class Entity;
class Component;
namespace component
{
class Transform;
class Texture;
}; // namespace component
} // namespace ecs
