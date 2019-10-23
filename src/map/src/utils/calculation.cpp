#include "utils/calculation.h"
#include "entity_system.h"

#include "random.h"
#include "components/basic_info.h"
#include "components/computed_values.h"
#include "components/level.h"
#include "components/life.h"
#include "components/magic.h"
#include "components/stamina.h"
#include "components/lua.h"
#include "components/position.h"
#include "components/skills.h"
#include "components/stats.h"
#include "components/inventory.h"

using namespace RoseCommon;

namespace Calculations {
  float get_runspeed(EntitySystem& entitySystem, RoseCommon::Entity entity) {
    //const auto& basicInfo = entitySystem.get_component<Component::BasicInfo>(entity);
    const auto& stats = entitySystem.get_component<Component::Stats>(entity);
    auto& values = entitySystem.get_component<Component::ComputedValues>(entity);
    float moveSpeed = 0;

    if (values.moveMode <= MoveMode::RUN) {
      int itemSpeed = 65, itemNumber = 0;

      if(entitySystem.has_component<Component::Inventory>(entity) == true) {
        auto& inventory = entitySystem.get_component<Component::Inventory>(entity);
        const auto& boots = inventory.boots();
        if(boots) {
          if(entitySystem.has_component<Component::ItemLua>(boots) == true) {
            auto& lua = entitySystem.get_component<Component::ItemLua>(boots);
            if(auto api = lua.api.lock(); api)
              itemSpeed = api->get_move_speed(); // Override the default item speed
          }
        }

        const auto& backpack = inventory.backpack();
        if(backpack) {
          if(entitySystem.has_component<Component::ItemLua>(backpack) == true) {
            auto& lua = entitySystem.get_component<Component::ItemLua>(backpack);
            if(auto api = lua.api.lock(); api)
              itemSpeed += api->get_move_speed();
          }
        }
      }
      itemSpeed += 20;

      moveSpeed = itemSpeed * (stats.dex + 500.f) / 100.f + 0; // TODO: Change 0 to value calcd from buffs for movement speed
      //passiveSpeed = passiveSkillValueMoveSpeed + moveSpeed * passiveSkillRateMoveSpeed / 100.f
      float passiveSpeed = 0 + moveSpeed * 0 / 100.f;
      moveSpeed += passiveSpeed;
    } else {
      // We are riding a cart/gear

      moveSpeed = 200;

      moveSpeed += 0;  // Get buffs value for movement speed

      //if (get_weight(entitySystem, entity) >= 100 && moveSpeed > 300) moveSpeed = 300;
    }
    values.runSpeed = moveSpeed;
    return moveSpeed;
  }

  float get_attackspeed(EntitySystem& entitySystem, RoseCommon::Entity entity) {
    const auto& stats = entitySystem.get_component<Component::Stats>(entity);
    auto& values = entitySystem.get_component<Component::ComputedValues>(entity);
    float weaponAtkSpd = 8, passiveAtkSpeed = 0;

    if(entitySystem.has_component<Component::Inventory>(entity) == true) {
      auto& inventory = entitySystem.get_component<Component::Inventory>(entity);
      const auto& weapon_r = inventory.weapon_r();
      if(weapon_r) {
        if(entitySystem.has_component<Component::ItemLua>(weapon_r) == true) {
          auto& lua = entitySystem.get_component<Component::ItemLua>(weapon_r);
          if(auto api = lua.api.lock(); api)
            weaponAtkSpd = api->get_attack_speed();
        }
      }
    }
    //Note: passiveAtkSpeed is only set depending on your job?
    float attackSpeed = (passiveAtkSpeed + 1500.f / (weaponAtkSpd + 5));
    //TODO: Do buff processing here
    //attackSpeed + attack speed buff - attack speed debuff
    if(attackSpeed < 30)
      attackSpeed = 30;

    values.atkSpeed = attackSpeed;
    return attackSpeed;
  }

  int get_weight(EntitySystem& entitySystem, RoseCommon::Entity entity) {
    return 0;
  }

  int get_maxhp(EntitySystem& entitySystem, RoseCommon::Entity entity) {
    auto& life = entitySystem.get_component<Component::Life>(entity);
    //TODO do calc here
    return 0;
  }

  int get_maxmp(EntitySystem& entitySystem, RoseCommon::Entity entity) {
    auto& magic = entitySystem.get_component<Component::Magic>(entity);
    //TODO do calc here
    return 0;
  }

  int get_successrate(EntitySystem& entitySystem, RoseCommon::Entity attacker, RoseCommon::Entity defender) {
    int success_rate = 0;
    //TODO do calc here
    return success_rate;
  }

  int64_t get_magicdamage(EntitySystem& entitySystem, RoseCommon::Entity attacker, RoseCommon::Entity defender, int hit_count, int success_rate) {
    //TODO
    return 50;
  }

  int64_t get_basicdamage(EntitySystem& entitySystem, RoseCommon::Entity attacker, RoseCommon::Entity defender, int hit_count, int success_rate) {
    int64_t damage = 0, critChance = 0;
    const auto& attackerLevel = entitySystem.get_component<Component::Level>(attacker);
    const auto& values = entitySystem.get_component<Component::ComputedValues>(attacker);

    //critChance = (int)(28 - ((values.critChance / 2.0f + attackerLevel.level) / (attackerLevel.level + 8)) * 20) + 1 + Core::Random::getInstance().get_uniform(0, 100);

    return 50;
  }

  int64_t get_damage(EntitySystem& entitySystem, RoseCommon::Entity attacker, RoseCommon::Entity defender, int hit_count) {
    auto successRate = get_successrate(entitySystem, attacker, defender);

    if(successRate < 20) {
      const auto& attackerLevel = entitySystem.get_component<Component::Level>(attacker);
      const auto& defenderLevel = entitySystem.get_component<Component::Level>(defender);

      if ( (int)(1 + Core::Random::getInstance().get_uniform(0, 100) + (attackerLevel.level - defenderLevel.level) * 0.6f) < 94 )
        return 0;
    }

    const auto& values = entitySystem.get_component<Component::ComputedValues>(attacker);
    // if(values.magicDamage)
    //   return get_magicdamage(entitySystem, attacker, defender, hit_count, successRate);

    return get_basicdamage(entitySystem, attacker, defender, hit_count, successRate);
  }
}