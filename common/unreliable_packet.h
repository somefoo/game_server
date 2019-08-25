#pragma once
#define PLAYER_STATE 130
#define ALL_PLAYER_STATE 130
#define PLAYER_STATE_START 1024

//https://www.gabrielgambetta.com/client-server-game-architecture.html
struct action{
  //angle relative to north
  float move_direction;
  //Amount of strength used to move (0,255)
  uint8_t move_strength;



  //Did shoot?
  uint8_t shoot : 1;
}

template <uint8_t N>
struct player_states{
  uint16_t m_type = PLAYER_STATE_START + N;
  player_state[N];
}
struct player_state{
  uint16_t m_type = PLAYER_STATE;
  uint8_t m_player_id;
  action m_action;
}

struct player_action{
  player_state m_player_state;
  action m_action;
}

struct packet{
  uint16_t m_type;
  uint8_t data[400];
}
