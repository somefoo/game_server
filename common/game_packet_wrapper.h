#pragma once
#include <optional>
#include "game_packet.h"
#include <enet/enet.h>
#include <memory>
///Owner of the ENet packet, cleans up all packets after going out of scope
///Explicit use of enet_packet_destroy is not needed if this object owns the pointer
class game_packet_wrapper {
 public:
   ///Careful, transfert of ownership here!
  game_packet_wrapper(std::unique_ptr<ENetPacket, decltype (&enet_packet_destroy)> packet)
      : m_packet(std::move(packet)) {}
 game_packet_wrapper(ENetPacket* packet)
      : m_packet(std::unique_ptr<ENetPacket, decltype(&enet_packet_destroy)>(packet, &enet_packet_destroy)) {}
/*
  ~game_packet_wrapper(){
    enet_packet_destroy(m_packet);
  }

  //No copying
  game_packet_wrapper(const game_packet_wrapper&) = delete;
  //No assignment
  auto operator=(const game_packet_wrapper&) = delete;
  //No moving
  game_packet_wrapper(const game_packet_wrapper&&) = delete;
  //No move assignment
  auto operator=(const game_packet_wrapper&&) = delete;
*/

  template <typename T>
  ///Warning, can return null if requested packet type is not valid
  constexpr T const * const get_packet() const{
    return interpret_as_packet<T>(m_packet->data, m_packet->dataLength);
  }

 private:
  std::unique_ptr<ENetPacket, decltype(&enet_packet_destroy)> m_packet;
  //std::unique_ptr<ENetPacket> m_packet_o;
  //ENetPacket* m_packet;
};
