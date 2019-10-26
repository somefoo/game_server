#pragma once
#include "global_player_state.h"

class global_state {
  public:
  int update(const uint8_t *const content, const size_t length){
    const player_action* pa;
    pa = interpret_as_packet<const player_action>(content,length);
    if(pa){
      m_player_state.update(pa);
      return 0;
    }
    return 1;
  }
  int set(const uint8_t *const content, const size_t length){
    const player_runtime_state<MAX_PLAYER_COUNT>* prs;
    prs = interpret_as_packet<const player_runtime_state<MAX_PLAYER_COUNT>>(content,length);
    if(prs){
      m_player_state.set_data(prs);
      return 0;
    }
    return 1;
  }

  constexpr std::pair<const uint8_t* const, const size_t> get(void) const{
    //TODO Once we have more than one state, we can construct the needed packets here!
    const auto[content, length] = m_player_state.get_state_packet();
    return std::make_pair(reinterpret_cast<const uint8_t*const>(content), length);
  }

  constexpr const player_runtime_state<MAX_PLAYER_COUNT>* get_player_state(void) const{
    return m_player_state.get_state(); 
  }


  private:
    global_player_state m_player_state;

};
