#include "../headers/Graph.hpp"
#include "../headers/Render.h"

int main() {
  Graph graph("../input.json", "../output.json");
  Render render(graph);

  render.Init();
  render.Draw();

  return 0;
}