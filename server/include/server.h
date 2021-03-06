#pragma once
#include <string>
#include <enet/enet.h>
#include <vector>
#include <game.h>
class server{
  public:
    server();
    int start(const uint16_t port);
    bool is_running(void) const;
    int start_server(void);
    int broadcast_state_reliable(void);
    int broadcast_state_fast(void);
    void kill();
  private:
    ENetHost* m_host;
    ENetPeer* m_clients[32 /*MAX_PLAYER_COUNT*/];

    uint8_t m_current_player_count;
    mutable uint32_t current_message_id; //Enable mutation in const functions
    game m_game;


    bool m_kill = false;
    char m_player1[3] = {'p','1','\0'}; //For testing
};
