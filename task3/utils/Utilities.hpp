#ifndef UTILITIES_H
#define UTILITIES_H

#include "../headers/MessageTemplate.hpp"
#include "../headers/QueryFilter.hpp"
#include <string>
#include <vector>

namespace utils {
std::vector<Message> ReadFile(const std::string &filePath);
Message ParseLine(const std::string &line);
std::vector<Message> Query(const std::vector<Message> &messages,
                           const QueryFilter &filter);
} // namespace utils

#endif