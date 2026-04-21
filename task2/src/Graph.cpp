#include "../headers/Graph.hpp"
#include "../headers/Constants.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

using json = nlohmann::json;

void Graph::LoadGraphFromFile(const std::string &filePath) {
  std::string fileString;
  std::ifstream file;

  file.open(filePath);

  if (file.is_open()) {
    json data = json::parse(file);

    for (auto &nodeJson : data["nodes"]) {
      Node n;
      n.id = nodeJson["id"];
      n.name = nodeJson["name"];
      n.x = 0;
      n.y = 0;
      nodes.push_back(n);
    }

    for (auto &edgeJson : data["edges"]) {
      int from = edgeJson["from"];
      int to = edgeJson["to"];
      adjacency[from].push_back(to);
    }
  } else {
    std::cerr << "ERROR::FILE_NOT_READ_SUCCESFULLY\n";
  }
}

void Graph::ComputeLayout() {
  std::unordered_set<int> childNodes{};
  int rootNode{};
  for (const auto &relation : adjacency) {
    for (size_t i = 0; i < relation.second.size(); i++) {
      childNodes.emplace(relation.second[i]);
    }
  }

  for (const auto &node : nodes) {
    if (childNodes.find(node.id) == childNodes.end()) {
      rootNode = node.id;
      break;
    }
  }

  std::queue<std::pair<int, int>> nodeQueue;
  nodeQueue.push({rootNode, 0});

  std::unordered_map<int, int> depthMap;

  // process nodes
  while (!nodeQueue.empty()) {
    auto [nodeID, depth] = nodeQueue.front();
    nodeQueue.pop();

    depthMap[nodeID] = depth;
    for (auto &child : adjacency[nodeID]) {
      nodeQueue.push({child, depth + 1});
    }
  }

  std::unordered_map<int, int> depthCount;
  for (auto &node : nodes) {
    int depth = depthMap[node.id];
    node.x = constants::X_OFFSET + depth * constants::X_SPACING;
    node.y = constants::Y_OFFSET + depthCount[depth] * constants::Y_SPACING;
    ++depthCount[depth];
  }
}

void Graph::SaveToFile(const std::string &filePath) {
  json data;
  data["nodes"] = json::array();
  data["edges"] = json::array();

  for (const auto &node : nodes) {
    data["nodes"].push_back(
        {{"id", node.id}, {"name", node.name}, {"x", node.x}, {"y", node.y}});
  }

  for (const auto &relation : adjacency) {
    for (int to : relation.second) {
      data["edges"].push_back({{"from", relation.first}, {"to", to}});
    }
  }

  std::ofstream file(filePath);
  file << data.dump(4);
}