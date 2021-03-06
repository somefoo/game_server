#include "client.h"
#include <memory>
#include <string>
#include <enet/enet.h>
#include <game_packet.h>
#include <game_packet_wrapper.h>
#include "logger.h"
#include <cstring>

client::client(void) {
  m_client = enet_host_create(NULL, 1, 2, 0, 0);
  if (m_client == nullptr) {
    logger::info("Could not create host.");
    exit(EXIT_FAILURE);
  }
}

client::~client(void) {
  // enet cleanup
  enet_host_destroy(m_client);
}

int client::connect(void) {
  if (enet_initialize() != 0) {
    logger::error("An error occurred while initialising server manager.");
    return 1;
  }
  std::string server_name = "pserver.cloud";
  //std::string server_name = "127.0.0.1";
  m_client = enet_host_create(NULL, 1, 2, 0, 0);
  if (!m_client) {
    logger::error("Failed to create client.");
    return 1;
  }

  ENetAddress address;
  ENetEvent event;

  enet_address_set_host(&address, server_name.data());
  address.port = 1234;

  m_peer = enet_host_connect(m_client, &address, 2, 0);
  if (!m_peer) {
    logger::error("No available m_peer for initiating connection.");
    return 1;
  }

  logger::info("Trying to connect to: ", server_name, ":", address.port);
  if (enet_host_service(m_client, &event, 1000) > 0 &&
      event.type == ENET_EVENT_TYPE_CONNECT) {
    logger::info("Connection succeeded.");
    //...
  } else {
    logger::error("Connection failed.");
    enet_peer_reset(m_peer);
    return 1;
  }

  return 0;
}

int client::send(const game_packet_wrapper& game_packet){
  //TODO return meaningful value
  m_game.update_and_send(game_packet, *m_client, *m_peer);
  return 0;
}

int client::poll_state(){
  ENetEvent event;
  //const player_runtime_state<MAX_PLAYER_COUNT>* tmp; 
  if(enet_host_service(m_client, &event, 0) > 0){
    if(event.type == ENET_EVENT_TYPE_RECEIVE){
      game_packet_wrapper packet(std::move(event.packet));
      m_game.set(packet);
      return 1;
    }
  }

/*
    switch(event.type){
      case ENET_EVENT_TYPE_RECEIVE:
        logger::verbose("I received a packed!");
        m_global_state.set(event.packet->data, event.packet->dataLength);
        enet_packet_destroy(event.packet);
        break;
      default:
        break;

    }
  }
  */
  return 0;
}

const game_state client::get_game_state() const{
  return m_game.get();
}
