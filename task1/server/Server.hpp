#ifndef SERVER_H
#define SERVER_H

#include "../headers/Ticket.hpp"
#include <atomic>
#include <cstdint>
#include <mutex>
#include <string_view>
#include <thread>
#include <vector>

class Server {
private:
  std::vector<Ticket> tickets{};
  std::mutex ticketMutex{};
  std::thread timeoutThread{};
  std::atomic<bool> running{true};

public:
  Server();
  ~Server();
  std::vector<Ticket> GetAvailable();
  bool Reserve(uint16_t ticketID, std::string_view owner);
  void Cancel(uint16_t ticketID, std::string_view owner);
  void Confirm(uint16_t ticketID, std::string_view owner);
  void CheckTimeout();
};

#endif