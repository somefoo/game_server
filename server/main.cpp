#include <enet/enet.h>
#include <iostream>
#include "logger.h"
int main(int argc, char **argv) {
  if (enet_initialize() != 0) {
    logger::error("An error occurred while initialising server manager.");
    return EXIT_FAILURE;
  }
  logger::info("Server manager initilised.");

  ENetAddress address;
  ENetHost *server;
  address.host = ENET_HOST_ANY;
  address.port = 1234;
	server = enet_host_create (&address, 32, 2, 0, 0);

	if(server == nullptr){
    logger::error("An error occurred while initialising server.");
    return EXIT_FAILURE;
	}

  atexit(enet_deinitialize);
  return (0);
}
