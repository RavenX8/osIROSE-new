#pragma once

#include "system.h"

namespace Systems {

class SpawnerSystem : public System {
 public:
  SpawnerSystem(SystemManager &manager);
  virtual ~SpawnerSystem() = default;

  virtual void update(EntityManager &es, double dt);
};

}  // namespace Systems
