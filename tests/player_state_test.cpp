#include <player_state.h>
#include <iostream>

player_state ps;
int main(){
  game_packet_wrapper gpw = make_game_packet_wrapper<packet<player_action>>(0, 0.0f, 3.1415, 255, 1);
  gpw.print_content();
  ps.update(gpw);

  auto* prs = ps.get().get_packet<player_runtime_state<MAXIMUM_PLAYER_COUNT>>(); 
  if(!prs){
    logger::error("Packet returned from player_state - game_packet_wrapper was null.");
    logger::error("Expected pointer to player_runtime_state<*>");
  }

  player_runtime_data& prt = prs->m_player_runtime_data[0];
  if(prt.m_position.x < 0.9 || prt.m_position.x > 1.1) return 1;
  if(prt.m_turret_angle < 3.1 || prt.m_position.x > 3.2) return 1;
  ps.update(gpw);
  if(prt.m_position.x < 1.9 || prt.m_position.x > 2.1) return 1;
  if(prt.m_turret_angle < 6.2 || prt.m_position.x > 6.4) return 1;

  logger::info("m_position.x           : ", prt.m_position.x);
  logger::info("m_position.y           : ", prt.m_position.y);
  logger::info("m_life                 : ",(int) prt.m_life);
  logger::info("m_player_id            : ",(int) prt.m_player_id);
  logger::info("m_turrent_angle        : ", prt.m_turret_angle);
  logger::info("m_current_projectiles  : ",(int) prt.m_current_projectiles);
  return 0;

}
