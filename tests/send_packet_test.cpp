#include <iostream>
#include <thread>
#include <chrono>
#include "client.h"
#include "server.h"

int server_fail = 0;
int client_fail = 0;

server s;
client c;

void run_server(void){
  server_fail = s.start_server();
}

void run_client(void){
  client_fail = c.connect();
  c.send_reliable("abc",4);
}

int main(){
  std::thread server_thread(&run_server);
  std::thread client_thread(&run_client);
 
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  s.kill();
  
  client_thread.join();
  server_thread.join();


  return server_fail | client_fail;
}


