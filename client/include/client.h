#pragma once
#include <enet/enet.h>
#include <game_packet.h>
#include <player_state.h>
#include <game_packet_wrapper.h>
//http://lists.cubik.org/pipermail/enet-discuss/2010-January/001308.html
class client{
  public:
  client(void);
  ~client(void);
  int connect(void);
  int send(const game_packet_wrapper& game_packet);
  int send_reliable(const char* content, const size_t length) const;
  int send_fast(const char* content, const size_t length) const;
  int poll_state(void);
  player_runtime_state<32> const* get_player_state(void) const;
  private:
    ENetHost *m_client;
  	ENetPeer *m_peer;
    player_state m_player_state;
};
