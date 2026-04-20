#include "../headers/Constants.hpp"
#include "../headers/Graph.hpp"
#include <gtest/gtest.h>

TEST(LayoutTest, RootNodeAtCorrectX) {
  Graph graph("../input.json");
  auto nodes = graph.GetNodes();
  auto root = nodes[0];
  EXPECT_EQ(root.x, constants::X_OFFSET);
}

TEST(LayoutTest, ChildrenHaveGreaterX) {
  Graph graph("../input.json");
  auto nodes = graph.GetNodes();
  EXPECT_GT(nodes[1].x, nodes[0].x);
  EXPECT_GT(nodes[2].x, nodes[1].x);
}

TEST(LayoutTest, SameDepthNodesDifferentY) {
  Graph graph("../input.json");
  auto nodes = graph.GetNodes();
  // nodes 3 and 4 are both at depth 2
  EXPECT_EQ(nodes[2].x, nodes[3].x);
  EXPECT_NE(nodes[2].y, nodes[3].y);
}

TEST(LayoutTest, NoNodeAtOrigin) {
  Graph graph("../input.json");
  auto nodes = graph.GetNodes();
  for (const auto &node : nodes) {
    EXPECT_NE(node.x, 0);
  }
}