#ifndef NODE_H
#define NODE_H

#include <string>

struct Node {
  uint16_t id{};
  std::string name{};
  int x{};
  int y{};
};

#endif