#pragma once
#include "enet/enet.h"
//http://lists.cubik.org/pipermail/enet-discuss/2010-January/001308.html
class client{
  public:
  client(void);
  ~client(void);
  int connect(void);
  int send_reliable(const char* content, const size_t length) const;
  int poll(void);
  private:
    ENetHost *m_client;
  	ENetPeer *m_peer;

};
