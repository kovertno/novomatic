#include "Server.hpp"
#include "../headers/Ticket.hpp"
#include <algorithm>
#include <cstdint>
#include <string_view>
#include <vector>

Server::Server() {
  Ticket t;
  t.id = 1;
  t.price = 350;
  t.name = "Normal";
  t.status = Availability::AVAILABLE;
  tickets.push_back(t);

  t.id = 3;
  t.price = 170;
  t.name = "Student";
  t.status = Availability::AVAILABLE;
  tickets.push_back(t);

  t.id = 4;
  t.price = 170;
  t.name = "Senior";
  t.status = Availability::AVAILABLE;
  tickets.push_back(t);

  t.id = 5;
  t.price = 200;
  t.name = "Reduced";
  t.status = Availability::AVAILABLE;
  tickets.push_back(t);

  timeoutThread = std::thread(&Server::CheckTimeout, this);
}

Server::~Server() {
  running = false;
  timeoutThread.join();
}

std::vector<Ticket> Server::GetAvailable() {
  std::vector<Ticket> out{};
  // protect ticket pool from concurrent access, RAII mutex lock
  std::lock_guard<std::mutex> lock(ticketMutex);
  for (auto &ticket : tickets) {
    if (ticket.status == Availability::AVAILABLE) {
      out.push_back(ticket);
    }
  }
  return out;
}

bool Server::Reserve(uint16_t ticketID, std::string_view owner) {
  std::lock_guard<std::mutex> lock(ticketMutex);
  auto it = std::find_if(tickets.begin(), tickets.end(),
                         [&](const Ticket &t) { return t.id == ticketID; });

  if (it == tickets.end()) {
    return false;
  }
  if (it->status != Availability::AVAILABLE) {
    return false;
  }
  it->status = Availability::RESERVED;
  it->owner = std::string(owner);
  it->reservedAt = std::chrono::steady_clock::now();
  return true;
}

void Server::Cancel(uint16_t ticketID, std::string_view owner) {
  std::lock_guard<std::mutex> lock(ticketMutex);
  auto it = std::find_if(tickets.begin(), tickets.end(),
                         [&](const Ticket &t) { return t.id == ticketID; });

  if (it == tickets.end()) {
    return;
  }
  if (it->owner != owner) {
    return;
  }
  if (it->status != Availability::RESERVED) {
    return;
  }
  it->status = Availability::AVAILABLE;
  it->owner = "";
}

void Server::Confirm(uint16_t ticketID, std::string_view owner) {
  std::lock_guard<std::mutex> lock(ticketMutex);
  auto it = std::find_if(tickets.begin(), tickets.end(),
                         [&](const Ticket &t) { return t.id == ticketID; });

  if (it == tickets.end()) {
    return;
  }
  if (it->owner != owner) {
    return;
  }
  if (it->status != Availability::RESERVED) {
    return;
  }
  it->status = Availability::SOLD;
}

void Server::CheckTimeout() {
  while (running) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::lock_guard<std::mutex> lock(ticketMutex);
    auto now = std::chrono::steady_clock::now();
    for (auto &ticket : tickets) {
      if (ticket.status == Availability::RESERVED) {
        if (now - ticket.reservedAt > std::chrono::seconds(60)) {
          ticket.status = Availability::AVAILABLE;
          ticket.owner = "";
        }
      }
    }
  }
}