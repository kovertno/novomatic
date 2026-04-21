#ifndef TICKET_H
#define TICKET_H

#include <chrono>
#include <cstdint>
#include <string>

enum class Availability { AVAILABLE, RESERVED, SOLD };

struct Ticket {
  uint16_t id{};
  int price{};
  std::string name{};
  Availability status = Availability::AVAILABLE;
  std::string owner;
  std::chrono::steady_clock::time_point reservedAt;
};

#endif