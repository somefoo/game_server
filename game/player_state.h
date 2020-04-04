#pragma once
#include "basic_state.h"
#include "game_packet.h"
#include <memory>
#include <cmath>
static constexpr uint8_t MAXIMUM_PLAYER_COUNT = 32;

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
