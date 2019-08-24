#include "enet/enet.h"
#include "client.h"
#include "logger.h"
#include <string>

client::client(void) {
  m_client = enet_host_create(NULL, 1, 2, 0, 0);
  if (m_client == nullptr){
    logger::info("Could not create host.");
    exit(EXIT_FAILURE);
  }
}

client::~client(void){
  //enet cleanup
  enet_host_destroy(m_client);
}

int client::connect(void){
	if(enet_initialize() != 0){
		logger::error("An error occurred while initialising server manager.");
		return 0;	
	}
	std::string server_name = "127.0.0.1";
  m_client = enet_host_create(NULL, 1, 2, 0, 0);
  if(!m_client){
    logger::error("Failed to create client.");
    return 0;
  }


  ENetAddress address;
  ENetEvent event;
  ENetPeer *peer;

  enet_address_set_host(&address, server_name.data());
  address.port = 1234;

  peer = enet_host_connect(m_client, &address, 2, 0);
  if(!peer){
    logger::error("No available peer for initiating connection.");
    return 0;
  }

  logger::info("Trying to connect to: ", server_name, ":", address.port);
  if(enet_host_service(m_client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT){
    logger::info("Connection succeeded."); 
    //...
  }else{
    logger::error("Connection failed.");
    enet_peer_reset(peer);
  }

  return 1;
}
