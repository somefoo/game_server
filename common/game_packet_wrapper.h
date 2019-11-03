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
  constexpr T const* const get_packet() const {
    return interpret_as_packet<T>(m_packet->data, m_packet->dataLength);
  }

  ///TODO is const really allowed here?
  ///TODO maybe its better not to flush here?
  ///Broadcasts message to all peers
  ///@param host the host which will broadcast to its peers
  void broadcast(ENetHost& host) const{
    enet_host_broadcast(&host, 0, m_packet.get());
    enet_host_flush(&host);
  }

  ///TODO is const really allowed here?
  ///TODO maybe its better not to flush here?
  ///Sends the packet to a specific peer
  ///@param host the host of the peer
  ///@param target the peer that the packet will be sent to
  void send(ENetHost& host, ENetPeer& target) const{
    enet_peer_send(&target, 0, m_packet.get()); 
    enet_host_flush(&host);
  }

 private:
  std::unique_ptr<ENetPacket, decltype(&enet_packet_destroy)> m_packet;
};
