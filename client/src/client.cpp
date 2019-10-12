#include "client.h"
#include <string>
#include <enet/enet.h>
#include <game_packet.h>
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
  }

  return 0;
}

int client::send_reliable(const char* content, const size_t length) const {
  ENetPacket* packet =
      enet_packet_create(content, length, ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send(m_peer, 0, packet);
  enet_host_flush(m_client);
  return 0;
}
int client::poll_state(){
  ENetEvent event;
  const player_runtime_state<MAX_PLAYER_COUNT>* tmp; 
  if(enet_host_service(m_client, &event, 0) > 0){
    switch(event.type){
      case ENET_EVENT_TYPE_RECEIVE:
        logger::verbose("I received a packed!");
        tmp = interpret_as_packet<const player_runtime_state<MAX_PLAYER_COUNT>>(event.packet->data, event.packet->dataLength);
        if(tmp){
          logger::verbose("CLIENT: Received packet was player_runtime_state<MAX_PLAYER_COUNT>"); 
          m_player_manager.set_data(tmp);
          //std::memcpy(prs, tmp, sizeof(player_runtime_state<32>));
        }else{
          logger::verbose("CLIENT: Received packet was NOT of expected type");
          logger::verbose("CLIENT:   Received packed was of type:", get_type(event.packet->data, event.packet->dataLength));
          logger::verbose("CLIENT:   But ", player_runtime_state<MAX_PLAYER_COUNT>::PACKET_TYPE, " was expected.");
        }
        enet_packet_destroy(event.packet);
        break;
      default:
        break;

    }
  }
  return 0;
}

const player_runtime_state<MAX_PLAYER_COUNT>* client::get_state(void) const{
  return m_player_manager.get_state();
}
