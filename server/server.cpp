#include <enet/enet.h>
#include <iostream>
#include "server.h"
#include "logger.h"

int server::start_server(void) {
  if (enet_initialize() != 0) {
    logger::error("An error occurred while initialising server manager.");
    return EXIT_FAILURE;
  }
  logger::info("Server manager initilised.");

  ENetAddress address;
  ENetHost *server;
  address.host = ENET_HOST_ANY;
  address.port = 1234;
  server = enet_host_create(&address, 32, 2, 0, 0);

  if (!server) {
    logger::error("An error occurred while initialising server.");
    logger::error("Failed to create server on ", address.host, ":",
                  address.port);
    return EXIT_FAILURE;
  }
  logger::info("Created server on ", address.host, ":", address.port);
  atexit(enet_deinitialize);

  ENetEvent event;
  while (1) {
    if (enet_host_service(server, &event, 100) > 0) {
      switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
          printf("A new client connected from %x:%u.\n",
                 event.peer->address.host, event.peer->address.port);

          /* Store any relevant client information here. */
          // event.peer->data = "Client information";

          break;

        case ENET_EVENT_TYPE_RECEIVE:
          printf(
              "A packet of length %u containing %s was received from % s on "
              "channel %u.\n ",
              event.packet->dataLength, event.packet->data, event.peer->data,
              event.channelID);

          /* Clean up the packet now that we're done using it. */
          enet_packet_destroy(event.packet);

          break;

        case ENET_EVENT_TYPE_DISCONNECT:
          printf("%s disconected.\n", event.peer->data);

          /* Reset the peer's client information. */

          event.peer->data = NULL;
      }
    }
    // Break if something happens HERE!!
  }

  enet_host_destroy(server);
  enet_deinitialize();
}
