#pragma once
#include <cstring>
#include "game_packet_wrapper.h"

template <uint16_t UNIQUE_ID, transfer_type TRANSFER>
struct container_header {
  constexpr const static uint16_t PACKET_TYPE = UNIQUE_ID;
  constexpr const static transfer_type TRANSFER_TYPE = TRANSFER;
};

template <typename DATA, transfer_type TRANSFER, uint16_t UNIQUE_ID>
struct stateless_data_container {
  constexpr const static uint16_t PACKET_TYPE = UNIQUE_ID;
  constexpr const static transfer_type TRANSFER_TYPE = TRANSFER;
};

template <typename DATA, transfer_type TRANSFER, uint16_t UNIQUE_ID>
struct state_data_container {
  constexpr const static uint16_t PACKET_TYPE = UNIQUE_ID;
  constexpr const static transfer_type TRANSFER_TYPE = TRANSFER;
  uint64_t m_state = 0;
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
  game_packet_wrapper m_state_packet = make_game_packet_wrapper<STATE_DATA>(STATE_DATA::TRANSFER_TYPE);

 protected:
  STATE_DATA& m_state = *m_state_packet.get_packet<STATE_DATA>();
};
