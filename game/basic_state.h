#pragma once
#include <cstring>
#include "game_packet_wrapper.h"

template <typename DATA, int ID>
struct stateless_data {
  constexpr const static uint16_t PACKET_TYPE = ID;
  DATA m_data;
};

template <typename DATA, int ID>
struct state_data {
  constexpr const static uint16_t PACKET_TYPE = ID;
  uint64_t m_state = 0;
  DATA m_data;
};

class base_state {
 public:
  virtual void update(const game_packet_wrapper& packet) = 0;
  virtual void set(const game_packet_wrapper& packet) = 0;
  virtual const game_packet_wrapper& get() const = 0;
  virtual ~base_state(){};
};

template <typename STATE_DATA>
class state : public base_state {
 public:
  void set(const game_packet_wrapper& packet) override {
    const auto* p = packet.get_packet<STATE_DATA>();
    if (!p) return;
    std::memcpy(&m_state, p, sizeof(*p));
  }
  const game_packet_wrapper& get() const override { return m_state_packet; }

 private:
  game_packet_wrapper m_state_packet = make_game_packet_wrapper<STATE_DATA>();

 protected:
  STATE_DATA& m_state = *m_state_packet.get_packet<STATE_DATA>();
};
