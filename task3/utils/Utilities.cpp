#include "Utilities.hpp"
#include "../headers/MessageTemplate.hpp"
#include "../headers/QueryFilter.hpp"
#include <string>
#include <vector>

#include <fstream>
#include <iostream>

static bool Matches(const Message &message, const QueryFilter &filter) {
  if (filter.logLevel.has_value() &&
      message.logLevel != filter.logLevel.value())
    return false;
  if (filter.source.has_value() && message.source != filter.source.value())
    return false;
  if (filter.timestampFrom.has_value() &&
      message.timestamp < filter.timestampFrom.value())
    return false;
  if (filter.timestampTo.has_value() &&
      message.timestamp > filter.timestampTo.value())
    return false;
  if (filter.message.has_value() &&
      message.message.find(filter.message.value()) == std::string::npos)
    return false;
  return true;
}

std::vector<Message> utils::ReadFile(const std::string &filePath) {
  std::vector<Message> out{};

  std::string fileString;
  std::ifstream file;

  file.open(filePath);

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      out.push_back(utils::ParseLine(line));
    }
  } else {
    std::cerr << "ERROR::FILE_NOT_READ_SUCCESSFULLY\n";
  }

  return out;
}

Message utils::ParseLine(const std::string &line) {
  Message message{};

  std::size_t start = line.find('[');
  std::size_t end = line.find(']');
  std::size_t prevEnd = end + 1;
  message.timestamp = line.substr(start + 1, end - start - 1);

  start = line.find('[', prevEnd);
  end = line.find(']', prevEnd);
  prevEnd = end + 1;
  message.logLevel = line.substr(start + 1, end - start - 1);

  start = line.find('[', prevEnd);
  end = line.find(']', prevEnd);
  prevEnd = end + 1;
  message.source = line.substr(start + 1, end - start - 1);

  message.message = line.substr(prevEnd + 1);

  return message;
}

std::vector<Message> utils::Query(const std::vector<Message> &messages,
                                  const QueryFilter &filter) {
  std::vector<Message> out;
  for (const Message &m : messages) {
    if (Matches(m, filter)) {
      out.push_back(m);
    }
  }
  return out;
}