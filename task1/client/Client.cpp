#include "Client.hpp"
#include <iostream>
#include <mutex>

void Client::Run() {
  {
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout << "[Client " << clientID << "] Starting purchase flow\n";
  }

  auto available = server.GetAvailable();
  {
    std::lock_guard<std::mutex> lock(printMutex);
    if (available.empty()) {
      std::cerr << "[Client " << clientID << "] No tickets available\n";
      return;
    }
  }

  // pick first available ticket
  Ticket chosen{};
  bool reserved = false;
  for (const auto &ticket : available) {
    if (server.Reserve(ticket.id, username)) {
      chosen = ticket;
      reserved = true;
      break;
    }
  }
  if (!reserved) {
    std::lock_guard<std::mutex> lock(printMutex);
    std::cerr << "[Client " << clientID << "] Could not reserve any ticket\n";
    return;
  }

  {
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout << "[Client " << clientID << "] Chose ticket: " << chosen.name
              << " (" << static_cast<float>(chosen.price) / 100.0f << " zl)\n";
  }

  {
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout << "[Client " << clientID << "] Reserved ticket " << chosen.id
              << "\n";
  }

  // insert coins
  int paid = 500;
  {
    std::lock_guard<std::mutex> lock(printMutex);

    std::cout << "[Client " << clientID << "] Inserted "
              << static_cast<float>(paid) / 100.0f << " zl\n";
  }

  auto change = coinMachine.CalculateChange(chosen.price, paid);

  // confirm or cancel
  if (!change.has_value()) {
    {
      std::lock_guard<std::mutex> lock(printMutex);
      std::cerr << "[Client " << clientID
                << "] Cannot make change - cancelling\n";
    }
    server.Cancel(chosen.id, username);
    return;
  }

  server.Confirm(chosen.id, username);

  {
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout << "[Client " << clientID
              << "] Purchase confirmed! Ticket: " << chosen.id
              << " Owner: " << username << "\n";
    std::cout << "[Client " << clientID << "] Change: ";

    for (auto &[coin, count] : change.value()) {
      std::cout << count << "x " << static_cast<float>(coin) / 100.0f << "zl  ";
    }
    std::cout << "\n";
  }
}