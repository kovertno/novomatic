#include "../headers/QueryFilter.hpp"
#include "../utils/Utilities.hpp"
#include <gtest/gtest.h>

#include <vector>

TEST(QueryTest, FilterBySource) {
  std::vector<Message> messages = utils::ReadFile("../logs.txt");
  QueryFilter filter;
  filter.source = "AuthService";

  std::vector<Message> result = utils::Query(messages, filter);

  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result[0].source, "AuthService");
  EXPECT_EQ(result[1].source, "AuthService");
}

TEST(QueryTest, FilterByLogLevelAndTimestamp) {
  std::vector<Message> messages = utils::ReadFile("../logs.txt");
  QueryFilter filter;
  filter.timestampFrom = "2023-10-25T10:00:00";
  filter.timestampTo = "2023-10-25T10:10:00";
  filter.logLevel = "ERROR";

  std::vector<Message> result = utils::Query(messages, filter);

  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].logLevel, "ERROR");
  EXPECT_EQ(result[0].source, "Database");
  EXPECT_EQ(result[0].timestamp, "2023-10-25T10:05:12");
}

TEST(QueryTest, FilterByMessage) {
  std::vector<Message> messages = utils::ReadFile("../logs.txt");
  QueryFilter filter;
  filter.message = "Transaction";

  std::vector<Message> result = utils::Query(messages, filter);

  EXPECT_EQ(result.size(), 2);
  EXPECT_NE(result[0].message.find("Transaction"), std::string::npos);
  EXPECT_NE(result[1].message.find("Transaction"), std::string::npos);
}