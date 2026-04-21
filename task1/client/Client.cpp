#include "Client.hpp"
#include <iostream>

void Client::Run() {
  std::cout << "[Client " << clientID << "] Starting purchase flow\n";

  auto available = server.GetAvailable();
  if (available.empty()) {
    std::cerr << "[Client " << clientID << "] No tickets available\n";
    return;
  }

  // pick first available ticket
  Ticket chosen = available[0];
  std::cout << "[Client " << clientID << "] Chose ticket: " << chosen.name
            << " (" << chosen.price << " zl)\n";

  if (!server.Reserve(chosen.id, username)) {
    std::cerr << "[Client " << clientID << "] Reservation failed\n";
    return;
  }
  std::cout << "[Client " << clientID << "] Reserved ticket " << chosen.id
            << "\n";

  // insert coins
  float paid = 5.00f;
  std::cout << "[Client " << clientID << "] Inserted " << paid << " zl\n";

  auto change = coinMachine.CalculateChange(chosen.price, paid);

  // confirm or cancel
  if (!change.has_value()) {
    std::cerr << "[Client " << clientID
              << "] Cannot make change - cancelling\n";
    server.Cancel(chosen.id, username);
    return;
  }

  server.Confirm(chosen.id, username);
  std::cout << "[Client " << clientID
            << "] Purchase confirmed! Ticket: " << chosen.id
            << " Owner: " << username << "\n";
  std::cout << "[Client " << clientID << "] Change: ";
  for (auto &[coin, count] : change.value()) {
    std::cout << count << "x " << coin << "zl  ";
  }
  std::cout << "\n";
}