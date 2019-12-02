#include "game_packet_wrapper.h"

///Internal type is a ENet packet
template <typename T>
struct state_base {
  void update(const game_packet_wrapper& packet) {
    T& underlying = static_cast<T&>(*this);
    underlying.update(packet);
  }

  void set(const game_packet_wrapper& packet){
    T& underlying = static_cast<T&>(*this);
    underlying.set(packet);
  }

  constexpr const game_packet_wrapper& get() const{
    T& underlying = static_cast<T&>(*this);
    return underlying.get();
  }
};

///Internal type is a simple packet
template <typename T, typename PT>
struct state_base_simple {
  void update(const game_packet_wrapper& packet) {
    T& underlying = static_cast<T&>(*this);
    underlying.update(packet);
  }

  void set(const game_packet_wrapper& packet){
    T& underlying = static_cast<T&>(*this);
    underlying.set(packet);
  }

  const PT * get_pointer_to_internal_packet() const{
    T& underlying = static_cast<T&>(*this);
    return underlying.get();
  }
};

