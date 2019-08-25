#pragma once
#include <string>
#include <enet/enet.h>
#include <vector>

class server{
  public:

    server(const uint8_t player_count);
    int start(const uint16_t port);
    bool is_running(void) const;
    int start_server(void);
    void kill();
  private:
    ENetHost* m_host;
    std::vector<ENetPeer*> m_clients;

    const uint8_t m_max_player_count; 
    uint8_t m_current_player_count;
    mutable uint32_t current_message_id; //Enable mutation in const functions

    bool m_kill = false;
    char m_player1[3] = {'p','1','\0'}; //For testing
};
