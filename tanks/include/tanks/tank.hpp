/*
 * tank.hpp - Tank Entity
 *
 * Author: frostzt
 * Date: 2026-02-08
 */
#pragma once

#include <cstdint>

namespace entity {

constexpr uint32_t PLAYER_TANK_MAX_HEALTH = 100;
constexpr uint32_t ENEMY_TANK_MAX_HEALTH = 3;

enum TankType {
  Player,
  Enemy,
  Boss,
};

class Tank {
private:
  uint32_t __health;

protected:
  TankType __tank_type;

public:
  Tank(uint32_t health, TankType tt) : __health(health), __tank_type(tt) {}

  virtual ~Tank() = default;

  virtual TankType get_tank_type() const = 0;
};

class PlayerTank : public Tank {
public:
  PlayerTank() : Tank(PLAYER_TANK_MAX_HEALTH, TankType::Player) {}

  /* Returns PlayerTank */
  TankType get_tank_type() const { return this->__tank_type; };
};
} // namespace entity
