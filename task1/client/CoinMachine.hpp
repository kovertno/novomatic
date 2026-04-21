#ifndef COIN_MACHINE_H
#define COIN_MACHINE_H

#include <map>
#include <optional>

class CoinMachine {
private:
  std::map<int, int, std::greater<int>> coins{};

public:
  CoinMachine();
  ~CoinMachine() = default;

  std::optional<std::map<int, int, std::greater<int>>>
  CalculateChange(int price, int paid);
};

#endif