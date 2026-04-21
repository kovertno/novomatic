#ifndef RENDER_H
#define RENDER_H

#include "Graph.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

class Render {
private:
  GLFWwindow *window = nullptr;
  const Graph *graph = nullptr;

public:
  Render(const Graph &graph) { this->graph = &graph; }

  ~Render() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
  };

  void Init();
  void Draw();
};

#endif