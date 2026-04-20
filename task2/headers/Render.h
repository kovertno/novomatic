#ifndef RENDER_H
#define RENDER_H

#include "Graph.hpp"
#include <GLFW/glfw3.h>

class Render {
private:
  GLFWwindow *window = nullptr;
  const Graph *graph = nullptr;

public:
  Render(const Graph &graph) { this->graph = &graph; }

  ~Render() {

  };

  void Init();
  void Draw();
};

#endif