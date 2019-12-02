#pragma once
#include "game_math.h"
#include <stdint.h>
#include <cstring>
#include <optional>
#include "logger.h"
#define PACKET_ERROR 1
#define PLAYER_ACTION 130
#define ALL_PLAYER_STATE 131
#define PLAYER_STATE_START 1024
#define PACKET_GAME_STATE_START 2048



//////////////// CLIENT -> SERVER ////////////////////////
// https://www.gabrielgambetta.com/client-server-game-architecture.html
struct player_action {
  constexpr const static uint16_t PACKET_TYPE = PLAYER_ACTION;
  player_action(uint8_t pi, float md, float ttd, uint8_t ms, uint8_t shoot){
    m_player_id = pi;
    m_move_direction = md;
    m_turret_turn_degree = ttd;
    m_move_strength = ms;
    m_shoot = shoot;//CAREFUL
  }
  uint8_t m_player_id;
  // angle relative to east
  float m_move_direction;
  // Turn turret amount
  float m_turret_turn_degree;
  // Amount of strength used to move (0,255)
  uint8_t m_move_strength;
  // Did shoot?
  uint8_t m_shoot : 1;

};

//////////////// SERVER -> CLIENT ////////////////////////
#define RUNTIME_STATE_START 2048
#define RUNTIME_EXTRA_START 3072

struct player_runtime_data {
  uint8_t m_player_id = 0;
  fvec2 m_position = 0;
  float m_turret_angle = 0.0f;
  uint8_t m_life = 0;
  uint8_t m_current_projectiles = 0;
  uint8_t m_kills = 0;
};

struct player_extra_data {
  uint8_t m_player_id;
  char m_name[16];
  char m_skin[16];
};

template <uint8_t N>
struct player_runtime_state{
  constexpr const static uint16_t PACKET_TYPE = RUNTIME_STATE_START + N - 1;
  player_runtime_data m_player_runtime_data[N];
};

template <uint8_t N>
struct player_extra_state{
  constexpr const static uint16_t PACKET_TYPE = RUNTIME_EXTRA_START + N - 1;
  player_extra_data m_player_extra_data[N];
};

//////////////// EXTRA ////////////////////////
//namespace{
//  enum packet_type : uint16_t{Error=0,Player_State=1};
//}
template<typename T>       
struct packet {                              
  uint16_t m_type = T::PACKET_TYPE;                           
  T m_packet;
  template<typename... ARGS>
  constexpr packet(ARGS&&... args) : m_packet(std::forward<ARGS>(args)...){}
};       

static constexpr uint16_t get_type(const uint8_t * data, size_t length){
  if(length < sizeof(uint16_t)) return PACKET_ERROR;
  //TODO Do checking if correct
  const uint16_t * const ret = reinterpret_cast<const uint16_t*>(data);
  return *ret;
}

template<typename T>
static constexpr T* interpret_as_packet(uint8_t * data, size_t length){
  if(get_type(data, length) == T::PACKET_TYPE && length == sizeof(packet<T>)){
    return reinterpret_cast<T*>(data + sizeof(packet<T>) - sizeof(T)); 
  }
  return nullptr;
}










//////////////// WHOLE GAME ////////////////////////
struct game_state {
  player_runtime_state<32> m_player_runtime_state;
  player_extra_state<32> m_player_extra_state;
};
