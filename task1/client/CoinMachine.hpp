#ifndef COIN_MACHINE_H
#define COIN_MACHINE_H

#include <map>
#include <optional>

class CoinMachine {
private:
  std::map<float, int, std::greater<float>> coins{};

public:
  CoinMachine();
  ~CoinMachine() = default;

  std::optional<std::map<float, int, std::greater<float>>>
  CalculateChange(float price, float paid);
};

#endif