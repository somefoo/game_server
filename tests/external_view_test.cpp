#include <iostream>
#include "client.h"

client c;

int main(){
  bool null_state = c.get_player_state() == nullptr;
  if(null_state){
    return 1;
  }
  return 0;
}


