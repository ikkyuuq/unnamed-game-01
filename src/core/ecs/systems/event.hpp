#pragma once

#include "core/ecs/event.hpp"
#include <algorithm>
#include <vector>

namespace ecs::sys
{
class EventListener
{
public:
  virtual ~EventListener() = default;
  virtual void onEvent(const Event &event) = 0;
};

class EventSystem
{
private:
  std::vector<EventListener *> listeners;

public:
  void add_listener(EventListener *listener) { listeners.push_back(listener); }
  void remove_listener(EventListener *listener)
  {
    listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
  }
  void notify(const Event &event)
  {
    for (auto *listener : listeners)
    {
      listener->onEvent(event);
    }
  }
};
}; // namespace ecs::sys
