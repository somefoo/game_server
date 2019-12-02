#pragma once
#include <enet/enet.h>
#include <game_packet.h>
#include <game.h>
#include <game_packet_wrapper.h>
//http://lists.cubik.org/pipermail/enet-discuss/2010-January/001308.html
class client{
  public:
  client(void);
  ~client(void);
  int connect(void);
  int send(const game_packet_wrapper& game_packet);
  int poll_state(void);
  const game_state get_game_state() const;
  private:
    ENetHost *m_client;
  	ENetPeer *m_peer;
    game m_game;
};
