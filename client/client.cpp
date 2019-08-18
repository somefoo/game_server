#include "enet/enet.h"
#include "client.h"
#include "logger.h"

client::client(void) {
  m_client = enet_host_create(NULL, 1, 2, 0, 0);
  if (m_client == nullptr){
    logger::info("Could not create host.");
    exit(EXIT_FAILURE);
  }
}
