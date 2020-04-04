#include <iostream>
#include <thread>
#include <chrono>
#include "client.h"
#include "server.h"
#include "game_packet.h"

int server_fail = 0;
int client_fail = 0;

server s;
client c;

void run_server(void){
  server_fail = s.start_server();
}

void run_client(void){
  client_fail = c.connect();
  for(uint8_t i = 0; i < 32; ++i){
      auto ps = make_game_packet_wrapper<player_action>(player_action{i, 3.14f, 2.14f, 127,1});
        client_fail |= c.send(ps);
  }

  for(uint8_t i = 0; i < 32; ++i){
      auto ps = make_game_packet_wrapper<player_action>(player_action{i, 24.12f, 45.14f, 255,0});
        client_fail |= c.send(ps);
  }

}

int main(){
  std::thread server_thread(&run_server);
  std::thread client_thread(&run_client);
 
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  

  s.broadcast_state_fast();
  std::this_thread::sleep_for(std::chrono::milliseconds(3));
  c.poll_state();

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  s.kill();
  client_thread.join();
  server_thread.join();


  return server_fail | client_fail;
}


