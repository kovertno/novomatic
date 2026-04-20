#include "../headers/MessageTemplate.hpp"
#include "../headers/QueryFilter.hpp"
#include "../utils/Utilities.hpp"
#include <iostream>
#include <vector>

int main() {
  std::vector<Message> messages = utils::ReadFile("../logs.txt");

  std::cout << "Test 1: Source = AuthService\n";
  QueryFilter f1;
  f1.source = "AuthService";
  for (const auto &m : utils::Query(messages, f1))
    std::cout << m.timestamp << " | " << m.logLevel << " | " << m.source
              << " | " << m.message << "\n";

  std::cout << "\nTest 2: ERROR between 10:00 and 10:10\n";
  QueryFilter f2;
  f2.logLevel = "ERROR";
  f2.timestampFrom = "2023-10-25T10:00:00";
  f2.timestampTo = "2023-10-25T10:10:00";
  for (const auto &m : utils::Query(messages, f2))
    std::cout << m.timestamp << " | " << m.logLevel << " | " << m.source
              << " | " << m.message << "\n";

  std::cout << "\nTest 3: Message contains Transaction\n";
  QueryFilter f3;
  f3.message = "Transaction";
  for (const auto &m : utils::Query(messages, f3))
    std::cout << m.timestamp << " | " << m.logLevel << " | " << m.source
              << " | " << m.message << "\n";

  return 0;
}
