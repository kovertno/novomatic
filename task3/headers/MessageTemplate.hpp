#ifndef MESSAGE_TEMPLATE_H
#define MESSAGE_TEMPLATE_H

#include <string>

struct Message {
  std::string timestamp{};
  std::string logLevel{};
  std::string source{};
  std::string message{};
};

#endif