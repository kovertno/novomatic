#ifndef GRAPH_H
#define GRAPH_H

#include "Node.hpp"

#include <unordered_map>
#include <vector>

class Graph {
private:
  std::vector<Node> nodes;
  std::unordered_map<int, std::vector<int>> adjacency;

  void LoadGraphFromFile(const std::string &filePath);
  void ComputeLayout();
  void SaveToFile(const std::string &filePath);

public:
  Graph(const std::string &inputPath, const std::string &outputPath = "") {
    LoadGraphFromFile(inputPath);
    ComputeLayout();
    if (!outputPath.empty()) {
      SaveToFile(outputPath);
    }
  }
  ~Graph() = default;

  const std::vector<Node> &GetNodes() const { return nodes; }

  const std::unordered_map<int, std::vector<int>> &GetAdjacency() const {
    return adjacency;
  }
};

#endif