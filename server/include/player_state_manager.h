#pragma once
#include <vector>
#include <game_math.h>
#include <game_packet.h>
#include <cassert>
#include <cmath>
//WARNING, NOT THREAD SAFE
template<uint8_t N>
class player_state_manager{
  public:
  constexpr player_state_manager() = default;
  //constexpr get_players_runtime_state() const;
  void update(const player_action& a){
    assert(a.m_player_id < N);
    player_runtime_data& p = m_runtime_state.m_player_runtime_data[a.m_player_id]; 
    const float dis_delta = float(a.m_move_strength) / 255.0f;
    const float pos_delta_x = std::cos(a.m_move_direction) * dis_delta;
    const float pos_delta_y = std::sin(a.m_move_direction) * dis_delta;
    const fvec2 pos_delta{pos_delta_x, pos_delta_y}; 

    //TODO realsitic check here
    logger::verbose("o_Player", std::to_string(a.m_player_id), " = (", p.m_position.x, ",", p.m_position.y, ")," , p.m_turret_angle);
    p.m_position += pos_delta;
    p.m_turret_angle += a.m_turret_turn_degree;
    logger::verbose("n_Player", std::to_string(a.m_player_id), " = (", p.m_position.x, ",", p.m_position.y, ")," , p.m_turret_angle);
  }

  constexpr std::pair<uint8_t, const packet<player_runtime_state<N>>*> get_runtime_state(void){
    return std::make_pair(m_current_count, &m_runtime_state_packet); 
  }

  constexpr uint8_t add_player(void){
    assert(m_current_count < N - 1);
    m_runtime_state.m_player_runtime_data[m_current_count].m_player_id = m_current_count;
    return m_current_count++; 
  }

  private:
  uint8_t m_current_count = 0;
  //We can't use std::array as we are doing some array magic
  //we don't have std::span yet
  packet<player_runtime_state<N>> m_runtime_state_packet;
  player_runtime_state<N> &m_runtime_state = m_runtime_state_packet.m_packet;
    
};
