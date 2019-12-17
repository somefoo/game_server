#pragma once
#include "game_packet_wrapper.h"
#include "player_state.h"

class game{
  public:
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
    player_state ps;
};
