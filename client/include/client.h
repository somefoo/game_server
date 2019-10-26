#pragma once
#include <enet/enet.h>
#include <game_packet.h>
#include <global_state.h>
//http://lists.cubik.org/pipermail/enet-discuss/2010-January/001308.html
class client{
  public:
  client(void);
  ~client(void);
  int connect(void);
  int send_reliable(const char* content, const size_t length) const;
  int send_fast(const char* content, const size_t length) const;
  int poll_state(void);
  player_runtime_state<MAX_PLAYER_COUNT> const* get_player_state(void) const;
  private:
    ENetHost *m_client;
  	ENetPeer *m_peer;
    global_state m_global_state;
};
