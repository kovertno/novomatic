#ifndef QUERY_FILTER_H
#define QUERY_FILTER_H

#include <optional>
#include <string>

struct QueryFilter {
  std::optional<std::string> timestampFrom{};
  std::optional<std::string> timestampTo{};
  std::optional<std::string> logLevel{};
  std::optional<std::string> source{};
  std::optional<std::string> message{};
};

#endif