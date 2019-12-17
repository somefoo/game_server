#pragma once
#include <enet/enet.h>
#include <memory>
#include <optional>
#include <logger.h>
static constexpr uint16_t PACKET_ERROR = 1;

template<typename T>
struct packet {
  uint16_t m_type = T::PACKET_TYPE;
  T m_packet;
  template<typename... ARGS>
  constexpr packet(ARGS&&... args) : m_packet(std::forward<ARGS>(args)...){}
};

static constexpr uint16_t get_type(const uint8_t * data, size_t length){
  if(length < sizeof(uint16_t)) return PACKET_ERROR;
  //TODO Do checking if correct
  const uint16_t * const ret = reinterpret_cast<const uint16_t*>(data);
  return *ret;
}

template<typename T>
static constexpr T* interpret_as_packet(uint8_t * data, size_t length){
  if(get_type(data, length) == T::PACKET_TYPE && length == sizeof(packet<T>)){
    return reinterpret_cast<T*>(data + sizeof(packet<T>) - sizeof(T));
  }
  return nullptr;
}
/// Owner of the ENet packet, cleans up all packets after going out of scope
/// Explicit use of enet_packet_destroy is not needed if this object owns the
/// pointer
class game_packet_wrapper {
 public:
  /// Careful, transfert of ownership here!
  game_packet_wrapper(
      std::unique_ptr<ENetPacket, decltype(&enet_packet_destroy)> packet)
      : m_packet(std::move(packet)) {
        //Prevent deallocation
        m_packet->referenceCount++;
      }
  /// Careful, transfert of ownership here!
  game_packet_wrapper(ENetPacket* packet)
      : m_packet(std::unique_ptr<ENetPacket, decltype(&enet_packet_destroy)>(
            packet, &enet_packet_destroy)) {
        //Prevent deallocation
        m_packet->referenceCount++;
      }

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


  /// Converts the packet content to text.
  /// Should be used for debugging only
  std::string get_text(){
    char text[m_packet->dataLength + 1];
    text[m_packet->dataLength] = '\0';
    return std::string(text);
  }


  //TODO remove
  void print_content() const{
    uint16_t packet_type = *reinterpret_cast<uint16_t*>(m_packet->data);
    logger::info("---");
    logger::info("type: ", packet_type);
    int counter = 0;
    for(uint8_t* i = m_packet->data + sizeof(uint16_t); i < m_packet->data + m_packet->dataLength; ++i){
      if(counter++ < 40)
      std::cout << (int)*i << " ";
      else
      std::cout << (int)*i << " " << '\n';
    }
    logger::info("---");
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
    std::unique_ptr obj = std::make_unique<packet<PK>>(std::forward<ARGS>(args)...);
    // NOTE: data is packet is now NOT initilised
    ENetPacket* const p = enet_packet_create(obj.get(), sizeof(packet<PK>), 0);
    auto ret = std::unique_ptr<ENetPacket, decltype(&enet_packet_destroy)>(
        p, &enet_packet_destroy);
    return game_packet_wrapper(std::move(ret));
    // NOTE: Copy data from standard initilised PK to enet_packet
}


