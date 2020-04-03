#pragma once
#include "game_packet_wrapper.h"
#include "game_packet.h"
#include "basic_state.h"
#include <vector>

class game{
  public:
    //Standard constructor
    game();
    //Update the local state only
    void update(const game_packet_wrapper& packet);
    //Update the local state and send 
    void update_and_send(const game_packet_wrapper& packet, ENetHost& host, ENetPeer& target);
    //Set the value of the local state only
    void set(const game_packet_wrapper& packet);
    //Broadcast the local state
    int broadcast_state(ENetHost& host) const;
    //Returns the state of the whole game
    const game_state get() const;
  private:
    std::vector<std::unique_ptr<base_state>> m_base_states;
};
