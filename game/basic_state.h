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
  /// Update the state if the game packet is relevant
  virtual void offer(const game_packet_wrapper& packet) = 0;
  /// Set the state if the game packet is relevant
  virtual void set(const game_packet_wrapper& packet) = 0;
  /// Returns the game packet
  virtual const game_packet_wrapper& get() const = 0;
  virtual ~base_state(){};
};

template <typename STATE_DATA, typename UPDATE_DATA>
class state : public base_state {
 public:
  void set(const game_packet_wrapper& packet) override final{
    const auto* p = packet.get_packet<STATE_DATA>();
    if (!p) return;
    std::memcpy(&m_state, p, sizeof(*p));
  }
  const game_packet_wrapper& get() const override final{ return m_state_packet; }

  void offer(const game_packet_wrapper& packet) override final{
    const auto* p = packet.get_packet<UPDATE_DATA>();
    if (!p) return;
    update(*p);
  }

  virtual void update(const UPDATE_DATA& update_data) = 0;

 private:
  game_packet_wrapper m_state_packet = make_game_packet_wrapper<STATE_DATA>();

 protected:
  STATE_DATA& m_state = *m_state_packet.get_packet<STATE_DATA>();
};
