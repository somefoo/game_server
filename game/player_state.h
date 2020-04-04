#pragma once
#include "basic_state.h"
#include "game_math.h"
#include <memory>
#include <cmath>

#define PLAYER_ACTION 130
#define ALL_PLAYER_STATE 131
#define PLAYER_STATE_START 1024
#define PACKET_GAME_STATE_START 2048
#define RUNTIME_STATE_START 2048
#define RUNTIME_EXTRA_START 3072


static constexpr uint8_t MAXIMUM_PLAYER_COUNT = 32;


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


struct player_runtime_data {
  uint8_t m_player_id = 0;
  fvec2 m_position = 0;
  float m_turret_angle = 0.0f;
  uint8_t m_life = 0;
  uint8_t m_current_projectiles = 0;
  uint8_t m_kills = 0;
};

template <uint8_t N>
struct player_runtime_state{
  constexpr const static uint16_t PACKET_TYPE = RUNTIME_STATE_START + N - 1;
  player_runtime_data m_player_runtime_data[N];
};

class player_state : public state<player_runtime_state<MAXIMUM_PLAYER_COUNT>, player_action>{
public:
  void update(const player_action& a) override{
    const float dis_delta = float(a.m_move_strength) / 255.0f;                                                                       
    const float pos_delta_x = std::cos(a.m_move_direction) * dis_delta;                                                              
    const float pos_delta_y = std::sin(a.m_move_direction) * dis_delta;                                                              
    const fvec2 pos_delta{pos_delta_x, pos_delta_y};                                                                                  

    //TODO realistic check here                                                                                                       
    logger::verbose("Updating player ", a.m_player_id, " with dpos=", pos_delta_x, ",", pos_delta_y, " ddeg=", a.m_turret_turn_degree);
    player_runtime_data& p = m_state.m_player_runtime_data[a.m_player_id];                                                   
    p.m_position += pos_delta;
    p.m_turret_angle += a.m_turret_turn_degree;
    logger::verbose("Updated player ", a.m_player_id, " with pos=", p.m_position.x, ",", p.m_position.y, " deg=", p.m_turret_angle);
  }
};
