#include <iostream>
#include <thread>
#include <chrono>
#include "server.h"
#include "game_packet.h"

int server_fail = 0;

server s;

void run_server(void){
  server_fail = s.start_server();
}

int main(){
  std::thread server_thread(&run_server);

  server_thread.join();
 
  return server_fail;
}


