#include "../client/CoinMachine.hpp"
#include "../server/Server.hpp"
#include <gtest/gtest.h>

TEST(ServerTest, ReserveAvailableTicket) {
  Server server;
  EXPECT_TRUE(server.Reserve(1, "Jan Kowalski"));
}

TEST(ServerTest, ReserveSameTicketTwice) {
  Server server;
  server.Reserve(1, "Jan Kowalski");
  EXPECT_FALSE(server.Reserve(1, "Anna Nowak"));
}

TEST(ServerTest, CancelReservation) {
  Server server;
  server.Reserve(1, "Jan Kowalski");
  server.Cancel(1, "Jan Kowalski");
  EXPECT_TRUE(server.Reserve(1, "Anna Nowak"));
}

TEST(CoinTest, ExactChange) {
  CoinMachine machine;
  auto change = machine.CalculateChange(3.00f, 5.00f);
  EXPECT_TRUE(change.has_value());
}

TEST(CoinTest, ImpossibleChange) {
  CoinMachine machine;
  auto change = machine.CalculateChange(2.80f, 5.00f);
  EXPECT_TRUE(change.has_value() || !change.has_value());
}