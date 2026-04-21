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

QueryFilter utils::ParseInput(const std::string &input) {
  QueryFilter out{};
  std::string filterBy{};

  filterBy = ExtractValue(input, "timestampFrom");
  if (!filterBy.empty())
    out.timestampFrom = filterBy;
  filterBy = "";

  filterBy = ExtractValue(input, "timestampTo");
  if (!filterBy.empty())
    out.timestampTo = filterBy;
  filterBy = "";

  filterBy = ExtractValue(input, "logLevel");
  if (!filterBy.empty())
    out.logLevel = filterBy;
  filterBy = "";

  filterBy = ExtractValue(input, "source");
  if (!filterBy.empty())
    out.source = filterBy;
  filterBy = "";

  filterBy = ExtractValue(input, "message");
  if (!filterBy.empty())
    out.message = filterBy;
  filterBy = "";

  return out;
}

std::string utils::ExtractValue(const std::string &input,
                                const std::string &key) {
  size_t start = input.find(key);
  if (start == std::string::npos) {
    return "";
  }

  start += key.size() + 2;
  size_t end = input.find("\"", start);

  return input.substr(start, end - start);
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