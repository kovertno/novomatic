#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include <thread>

int main() {
  Server server;

  // create 3 separate threads that communicate with the same server
  std::thread c1([&]() { Client(server, 1, "Jan Kowalski").Run(); });
  std::thread c2([&]() { Client(server, 2, "Anna Nowak").Run(); });
  std::thread c3([&]() { Client(server, 3, "Piotr Wisniewski").Run(); });

  c1.join();
  c2.join();
  c3.join();

  return 0;
}