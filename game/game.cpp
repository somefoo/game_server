#include "game_packet_wrapper.h"
#include "player_state.h"
#include "game.h"

game::game(){
  std::unique_ptr<base_state> ps_ptr = std::make_unique<player_state>();
  m_base_states.push_back(std::move(ps_ptr));
}

void game::update(const game_packet_wrapper& packet){
  for (auto& state : m_base_states){
    state->update(packet);
  }
}

void game::update_and_send(const game_packet_wrapper& packet, ENetHost& host, ENetPeer& target){
  for (auto& state : m_base_states){
    state->update(packet);
  }
  packet.send(host, target);
}

void game::set(const game_packet_wrapper& packet){
  for (auto& state : m_base_states){
    state->set(packet);
  }
}

int game::broadcast_state(ENetHost& host) const{
  for (auto& state : m_base_states){
    state->get().broadcast(host);
  }

  return 0;
}

const game_state game::get() const{
  //TODO is this correct?
  //game_state gs{};
  //gs.m_player_runtime_state = *(ps.get().get_packet<player_runtime_state<MAXIMUM_PLAYER_COUNT>>());
  //return gs;
  //TODO better?
  //TODO This has to be done differently
  return game_state{*(m_base_states[0]->get().get_packet<player_runtime_state<MAXIMUM_PLAYER_COUNT>>()), {}};
}
