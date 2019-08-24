#pragma once
#include "enet/enet.h"
//http://lists.cubik.org/pipermail/enet-discuss/2010-January/001308.html
class client{
  public:
  client(void);
  ~client(void);
  int connect(void);
  private:
    ENetHost * m_client;
};
