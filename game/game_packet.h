#pragma once
#include "player_state.h"

struct game_state {
    player_runtime_state<32> m_player_runtime_state;
    int other;
};

