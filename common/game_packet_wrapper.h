#pragma once
#include <enet/enet.h>
#include <memory>
#include <optional>
#include "game_packet.h"
/// Owner of the ENet packet, cleans up all packets after going out of scope
/// Explicit use of enet_packet_destroy is not needed if this object owns the
/// pointer
class game_packet_wrapper {
 public:
  /// Careful, transfert of ownership here!
  game_packet_wrapper(
      std::unique_ptr<ENetPacket, decltype(&enet_packet_destroy)> packet)
      : m_packet(std::move(packet)) {}
  /// Careful, transfert of ownership here!
  game_packet_wrapper(ENetPacket* packet)
      : m_packet(std::unique_ptr<ENetPacket, decltype(&enet_packet_destroy)>(
            packet, &enet_packet_destroy)) {}

  template <typename T>
  /// Warning, can return null if requested packet type is not valid
  constexpr T* get_packet() const {
    return interpret_as_packet<T>(m_packet->data, m_packet->dataLength);
  }

  /// TODO is const really allowed here?
  /// TODO maybe its better not to flush here?
  /// Broadcasts message to all peers
  ///@param host the host which will broadcast to its peers
  void broadcast(ENetHost& host) const {
    enet_host_broadcast(&host, 0, m_packet.get());
    enet_host_flush(&host);
  }

  /// TODO is const really allowed here?
  /// TODO maybe its better not to flush here?
  /// Sends the packet to a specific peer
  ///@param host the host of the peer
  ///@param target the peer that the packet will be sent to
  void send(ENetHost& host, ENetPeer& target) const {
    enet_peer_send(&target, 0, m_packet.get());
    enet_host_flush(&host);
  }

 private:
  std::unique_ptr<ENetPacket, decltype(&enet_packet_destroy)> m_packet;
};

///Creates a game_packet_wrapper from holding an ENet packet of type specified by PK
///@tparam PK the type of the packet that the ENet packet will hold
///@tparam ARGS The type of the argument list which will be used to initilise PK
///@param args The argument list which will be used to initilise PK 
template <typename PK, typename... ARGS>
game_packet_wrapper make_game_packet_wrapper(ARGS&&... args) {
    // I am creating a temporary object of type PK to use for initilisation of
    // enet packet data. The object will be deleted after funciton call.
    // I am aware this is ugly, but as enet is a C library, and this initiliser
    // is rarely used, the overhead is acceptable.
    // It is worth noting, ENet uses a custom allocator, so pointer swapping
    // is dangerous.
    std::unique_ptr obj = std::make_unique<PK>(std::forward<ARGS>(args)...);
    // NOTE: data is packet is now NOT initilised
    ENetPacket* const p = enet_packet_create(obj.get(), sizeof(PK), 0);
    auto ret = std::unique_ptr<ENetPacket, decltype(&enet_packet_destroy)>(
        p, &enet_packet_destroy);
    return game_packet_wrapper(std::move(ret));
    // NOTE: Copy data from standard initilised PK to enet_packet
}
