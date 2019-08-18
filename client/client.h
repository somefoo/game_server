#pragma once
#include "enet/enet.h"

class client{
  client(void);
  private:
    ENetHost * m_client;
};
