#pragma once
#include <string>

class server{
  public:
    int start_server(void);
    void kill();
  private:
    bool m_kill = false;
    char m_player1[3] = {'p','1','\0'}; //For testing
};
