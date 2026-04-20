#include "CoinMachine.hpp"
#include <map>
#include <optional>

CoinMachine::CoinMachine() {
  coins[5.00f] = 5;
  coins[2.00f] = 5;
  coins[1.00f] = 5;
  coins[0.50f] = 5;
  coins[0.20f] = 5;
  coins[0.10f] = 5;
}

std::optional<std::map<float, int, std::greater<float>>>
CoinMachine::CalculateChange(float price, float paid) {
  if (price > paid) {
    return {};
  }
  std::map<float, int, std::greater<float>> out{};
  float change = paid - price;

  auto tempCoins = coins;
  for (auto &coin : tempCoins) {
    if (coin.first > change) {
      continue;
    } else if (coin.second == 0) {
      continue;
    } else {
      while (coin.second > 0 && change >= coin.first) {
        change -= coin.first;
        --coin.second;
        ++out[coin.first];
        if (change < 0.01f) {
          coins = tempCoins;
          return out;
        }
      }
    }
  }

  return {};
}