#include "game_packet_wrapper.h"
#include "game.h"

void game::update(const game_packet_wrapper& packet){
  ps.update(packet);
}

void game::update_and_send(const game_packet_wrapper& packet, ENetHost& host, ENetPeer& target){
  update(packet);
  packet.send(host, target);
}

void game::set(const game_packet_wrapper& packet){
  ps.set(packet);
}

int game::broadcast_state(ENetHost& host) const{
  ps.get().broadcast(host);
  return 0;
}

const game_state game::get() const{
  //TODO is this correct?
  //game_state gs{};
  //gs.m_player_runtime_state = *(ps.get().get_packet<player_runtime_state<MAXIMUM_PLAYER_COUNT>>());
  //return gs;
  //TODO better?
  return game_state{*(ps.get().get_packet<player_runtime_state<MAXIMUM_PLAYER_COUNT>>()), 0};
}
