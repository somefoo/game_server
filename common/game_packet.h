#pragma once
#include "game_math.h"
#include <stdint.h>
#include <cstring>
#define ERROR 1
#define PLAYER_STATE 130
#define ALL_PLAYER_STATE 130
#define PLAYER_STATE_START 1024

//////////////// CLIENT -> SERVER ////////////////////////
// https://www.gabrielgambetta.com/client-server-game-architecture.html
struct action {
  // angle relative to east
  float move_direction;
  // Turn turret amount
  float turret_turn_degree;
  // Amount of strength used to move (0,255)
  uint8_t move_strength;
  // Did shoot?
  uint8_t shoot : 1;
};

struct player_state {
  uint16_t m_type = PLAYER_STATE;
  uint8_t m_player_id;
  action m_action;
};

struct player_action {
  player_state m_player_state;
  action m_action;
};

struct packet {
  uint16_t m_type;
  uint8_t data[400];
};

//////////////// SERVER -> CLIENT ////////////////////////
#define RUNTIME_STATE_START 2048
#define RUNTIME_EXTRA_START 3072

struct player_runtime_data {
  uint8_t m_player_id;
  fvec2 m_position;
  float m_turret_angle;
  uint8_t m_life;
  uint8_t m_current_projectiles;
  uint8_t m_kills;
};

struct player_extra_data {
  uint8_t m_player_id;
  char m_name[16];
  char m_skin[16];
};

template <uint8_t N>
struct player_runtime_state{
  uint16_t m_type = RUNTIME_STATE_START + N - 1;
  player_runtime_data m_player_runtime_data[N];
};

template <uint8_t N>
struct player_extra_state{
  uint16_t m_type = RUNTIME_STATE_START + N - 1; 
  player_extra_data m_player_extra_data[N];
};

//////////////// EXTRA ////////////////////////

static constexpr uint16_t get_type(const uint8_t * data, size_t length){
  if(length < sizeof(uint16_t)) return ERROR;
  //TODO Do checking if correct
  const uint16_t* r = reinterpret_cast<const uint16_t*>(data);
  return *r;
}
