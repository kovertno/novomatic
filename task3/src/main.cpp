#include "../headers/MessageTemplate.hpp"
#include "../headers/QueryFilter.hpp"
#include "../utils/Utilities.hpp"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  std::string filePath = argc > 1 ? argv[1] : "../logs.txt";
  std::vector<Message> messages = utils::ReadFile(filePath);

  std::cout << "Welcome to Task3\n";
  std::cout << "To exit the application type \" exit \"\n";
  std::cout << "The proper way to run query engine is to filter by:\n";
  std::cout << "TIMESTAMP FROM(timestampFrom)\n"
            << "TIMESTAMP TO(timestampTo)\n"
            << "LOG LEVEL(logLevel)\n"
            << "SOURCE(source)\n"
            << "MESSAGE(message)\n";
  std::cout << "\nExample use: logLevel=\"ERROR\" "
               "timestampFrom=\"2023-10-25T10:00:00\" "
               "timestampTo=\"2023-10-25T10:10:00\"\n";

  std::string currentInput{};
  while (true) {
    std::cout << "\n> ";
    std::getline(std::cin, currentInput);

    if (currentInput == "exit") {
      break;
    }

    QueryFilter filter = utils::ParseInput(currentInput);
    auto results = utils::Query(messages, filter);

    if (results.empty()) {
      std::cout << "No results found.\n";
    } else {
      for (const auto &m : results) {
        std::cout << "[" << m.timestamp << "] [" << m.logLevel << "] ["
                  << m.source << "] " << m.message << "\n";
      }
    }
  }

  return 0;
}
