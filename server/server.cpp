#include <enet/enet.h>
#include <iostream>
#include "server.h"
#include "logger.h"
#include "game_packet.h"
#define RELIABLE_CHANNEL 0
#define UNRELIABLE_CHANNEL 1

server::server() : m_current_player_count(0){
}

int server::start(const uint16_t port){
  ENetAddress address;
  address.host = ENET_HOST_ANY;
  address.port = port;
  //enet_address_set_host(&address, "localhost");
  m_host = enet_host_create(&address, MAX_PLAYER_COUNT, 2, 0, 0);
  if(!m_host){
    logger::error("Failed to create host on port ", port); 
    return EXIT_FAILURE;
  }
  logger::info("Created server on ", address.host, ":", address.port);
  return 0;
}

bool server::is_running(void) const{
  return m_host != nullptr;
}


void server::kill(void){
  m_kill = true;
}

int server::start_server(void) {
  if (enet_initialize() != 0) {
    logger::error("An error occurred while initialising server manager.");
    return EXIT_FAILURE;
  }
  logger::info("Server manager initilised.");

  start(1234);

  //atexit(enet_deinitialize);

  ENetEvent event;
  const player_action* pa;
  while (!m_kill) {
    if (enet_host_service(m_host, &event, 100) > 0) {
      switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
          logger::info("Client connected from: ", event.peer->address.host, ":", event.peer->address.port);
          logger::info("Client connect ID: ", event.peer->connectID);
          /* Store any relevant client information here. */
          event.peer->data = m_player1;

          break;

        case ENET_EVENT_TYPE_RECEIVE:
          logger::verbose("Packet received from peer with ID: ", event.peer->connectID);
          logger::verbose("Packet type: ", get_type(event.packet->data,event.packet->dataLength));
          pa = interpret_as_packet<const player_action>(event.packet->data, event.packet->dataLength);
          if(pa){
            m_player_manager.update(*pa);
          }else{
            logger::info("Received packet which was not a player_action packet.");
          }
          /* Clean up the packet now that we're done using it. */
          enet_packet_destroy(event.packet);

          break;

        case ENET_EVENT_TYPE_DISCONNECT:
          //printf("%s disconected.\n", event.peer->data);
          logger::info(event.peer->data, "disconnected.");

          /* Reset the peer's client information. */

          event.peer->data = NULL;
          break;
        case ENET_EVENT_TYPE_NONE:
          break;
      }
    }
    //TEMP SOLUTION
    broadcast_state();
    // Break if something happens HERE!!
  }

  enet_host_destroy(m_host);
  enet_deinitialize();
  return 0;
}

int server::broadcast_state(void){
  auto [count, data] = m_player_manager.get_runtime_state();
  //TODO remove fixed player count (MAX_PLAYER_COUNT)
  ENetPacket* enet_packet =
      enet_packet_create(data, sizeof(packet<player_runtime_state<MAX_PLAYER_COUNT>>), ENET_PACKET_FLAG_RELIABLE);
  enet_host_broadcast(m_host, 0, enet_packet);
  enet_host_flush(m_host);
  //SEND AND FLUSH
  return 0;
}
