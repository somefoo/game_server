#include <iostream>
#include "client.h"

client c;

int main(){
  if(c.get_game_state().m_player_runtime_state.m_player_runtime_data[0].m_kills != 0) return 1;
  return 0;
}


