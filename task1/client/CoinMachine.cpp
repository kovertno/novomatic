#include "CoinMachine.hpp"
#include <map>
#include <optional>

CoinMachine::CoinMachine() {
  coins[500] = 5;
  coins[200] = 5;
  coins[100] = 5;
  coins[50] = 5;
  coins[20] = 5;
  coins[10] = 5;
}

std::optional<std::map<int, int, std::greater<int>>>
CoinMachine::CalculateChange(int price, int paid) {
  if (price > paid)
    return {};

  std::map<int, int, std::greater<int>> out{};
  int change = paid - price;
  auto tempCoins = coins;

  for (auto &coin : tempCoins) {
    while (coin.second > 0 && change >= coin.first) {
      change -= coin.first;
      --coin.second;
      ++out[coin.first];
    }
    if (change == 0) {
      coins = tempCoins;
      return out;
    }
  }
  return {};
}