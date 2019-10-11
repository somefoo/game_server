#pragma once
#include <string>
#include <enet/enet.h>
#include <vector>
#include "player_state_manager.h"
#define MAX_PLAYER_COUNT 32
class server{
  public:
    server();
    int start(const uint16_t port);
    bool is_running(void) const;
    int start_server(void);
    int broadcast_state(void);
    void kill();
  private:
    ENetHost* m_host;
    ENetPeer* m_clients[MAX_PLAYER_COUNT];

    uint8_t m_current_player_count;
    mutable uint32_t current_message_id; //Enable mutation in const functions
    player_state_manager<MAX_PLAYER_COUNT> m_player_manager;


    bool m_kill = false;
    char m_player1[3] = {'p','1','\0'}; //For testing
};
