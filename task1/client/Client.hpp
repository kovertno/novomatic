#ifndef CLIENT_H
#define CLIENT_H
#include "../server/Server.hpp"
#include "CoinMachine.hpp"
#include <mutex>
#include <string>

class Client {
private:
  Server &server;
  CoinMachine coinMachine;
  std::string username;
  uint16_t clientID;
  inline static std::mutex printMutex;

public:
  Client(Server &server, uint16_t clientID, std::string_view username)
      : server(server), clientID(clientID), username(username) {}
  ~Client() = default;
  void Run();
};
#endif