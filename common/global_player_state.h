#pragma once
#include <vector>
#include "game_math.h"
#include "game_packet.h"
#include <cassert>
#include <cmath>
#define MAX_PLAYER_COUNT 32
//WARNING, NOT THREAD SAFE
//The idea is as following, each client and server holds one of these Objects.
//There are two methods to alter the state of the game:
//1) Player input - A player performs input, altering the game state for one player 
//2) Global set - The game state is set to a certain state, this state will usually be passed to each client by the server.
template<uint8_t N>
class global_player_state{
  public:
  constexpr global_player_state() = default;
  //constexpr get_players_runtime_state() const;
  void update(const player_action* const a){
    assert(a != nullptr);
    assert(a->m_player_id < N);
    player_runtime_data& p = m_runtime_state.m_player_runtime_data[a->m_player_id]; 
    const float dis_delta = float(a->m_move_strength) / 255.0f;
    const float pos_delta_x = std::cos(a->m_move_direction) * dis_delta;
    const float pos_delta_y = std::sin(a->m_move_direction) * dis_delta;
    const fvec2 pos_delta{pos_delta_x, pos_delta_y}; 

    //TODO realistic check here
    logger::verbose("o_Player", std::to_string(a->m_player_id), " = (", p.m_position.x, ",", p.m_position.y, ")," , p.m_turret_angle);
    p.m_position += pos_delta;
    p.m_turret_angle += a->m_turret_turn_degree;
    logger::verbose("n_Player", std::to_string(a->m_player_id), " = (", p.m_position.x, ",", p.m_position.y, ")," , p.m_turret_angle);
  }
  
  void set_data(const player_runtime_state<N>* const runtime_state_data){
    std::memcpy(&m_runtime_state.m_player_runtime_data, runtime_state_data, sizeof(const player_runtime_state<N>));
  }

  void set_packet(const packet<const player_runtime_state<N>>* const runtime_state_packet){
    std::memcpy(&m_runtime_state, runtime_state_packet, sizeof(packet<const player_runtime_state<N>>));
  }

  //TODO Change name; remove runtime
  constexpr std::pair<const packet<player_runtime_state<N>>*, size_t> get_state_packet(void) const{
    //TODO This needs to be adaptive later!
    return std::make_pair(&m_runtime_state_packet, sizeof(packet<player_runtime_state<N>>)); 
  }

  constexpr const player_runtime_state<N>* get_state(void) const{
    //return nullptr;
    return &(m_runtime_state); 
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
