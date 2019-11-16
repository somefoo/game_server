#include <player_state.h>
#include <game_packet_wrapper.h>
#include <game_packet.h>
#include <enet/enet.h>

int main(){
  //char data[]{'h','e','l','l','o'};
  packet<player_action> content(0,0,0,42,0);
  ENetPacket* enet_packet = enet_packet_create(&content, sizeof content, 0);
  
  game_packet_wrapper from_enet_packet(enet_packet);

  player_action* temp = interpret_as_packet<player_action>(enet_packet->data, enet_packet->dataLength);
  if(temp == nullptr){
    logger::error("interpret_as_packet<player_action>(enet_packet->data, enet_packet->dataLength) FAILED");
    return 1;
  }

  if(from_enet_packet.get_packet<player_action>() == nullptr){
    logger::error("from_enet_packet.get_packet<player_action>() FAILED");
    return 1; 
  }
  if(temp != from_enet_packet.get_packet<player_action>()){
    logger::error("moving from enet_packet to game_packet_wrapper caused COPYING");
    return 1;
  }
  if(from_enet_packet.get_packet<player_action>()->m_move_strength != 42){
    logger::error("expected 42 for m_move_strength");
    return 1;
  }





  player_state ps;
  ps.update(from_enet_packet);
  if(ps.get().get_packet<player_runtime_state<MAXIMUM_PLAYER_COUNT>>() == nullptr){
    logger::error("player_state broke after update.");
    return 1;
  }


}
