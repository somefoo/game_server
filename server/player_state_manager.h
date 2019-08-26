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
  void update(const action& a, const uint8_t player_id){
    assert(player_id < N);
    player_runtime_data& p = m_runtime_data[N]; 
    const float dis_delta = 255.0f / float(a.move_strength);
    const float pos_delta_x = std::cos(a.move_direction) * dis_delta;
    const float pos_delta_y = std::sin(a.move_direction) * dis_delta;
    const fvec2 pos_delta{pos_delta_x, pos_delta_y}; 

    //TODO realsitic check here
    p.m_position += pos_delta;
    p.m_turret_angle += a.turret_turn_degree;
  }

  constexpr std::pair<uint8_t, const player_runtime_data * const> get_runtime_data(void){
    return std::make_pair<uint8_t, const player_runtime_data *  const>(3, m_runtime_data); 
  }

  constexpr uint8_t add_player(void){
    assert(m_current_count < N - 1);
    m_runtime_data[m_current_count].m_player_id = m_current_count;
    return m_current_count++; 
  }

  private:
  uint8_t m_current_count = 0;
  player_runtime_data m_runtime_data[N]{0};
    
};
