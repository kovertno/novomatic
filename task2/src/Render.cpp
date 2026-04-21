#include "../headers/Render.h"
#include "../headers/Constants.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>

void Render::Init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  glfwSetErrorCallback([](int error, const char *desc) {
    std::cerr << "GLFW Error" << error << ": " << desc << std::endl;
  });

  window = glfwCreateWindow(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT,
                            "Task2", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);

  // create context for imgui and set up the window
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void Render::Draw() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImDrawList *drawList = ImGui::GetBackgroundDrawList();

    std::unordered_map<int, const Node *> nodeByID{};
    for (const auto &node : graph->GetNodes()) {
      nodeByID[node.id] = &node;
    }

    // draw edges
    for (const auto &[from, children] : graph->GetAdjacency()) {
      for (int to : children) {
        const Node *fromNode = nodeByID[from];
        const Node *toNode = nodeByID[to];

        ImVec2 fromPos(fromNode->x + constants::NODE_WIDTH / 2.0f,
                       fromNode->y + constants::NODE_HEIGHT / 2.0f);
        ImVec2 toPos(toNode->x + constants::NODE_WIDTH / 2.0f,
                     toNode->y + constants::NODE_HEIGHT / 2.0f);

        drawList->AddLine(fromPos, toPos, IM_COL32(255, 255, 255, 255), 2.0f);
      }
    }

    // draw nodes
    for (const auto &node : graph->GetNodes()) {
      ImVec2 topLeft(node.x, node.y);
      uint16_t additionalWidth = 5;
      ImVec2 textParams = ImGui::CalcTextSize(node.name.c_str());

      ImVec2 bottomRight(node.x + textParams.x + 2 * additionalWidth,
                         node.y + constants::NODE_HEIGHT);
      drawList->AddRectFilled(topLeft, bottomRight,
                              IM_COL32(70, 130, 180, 255));
      drawList->AddRect(topLeft, bottomRight, IM_COL32(255, 255, 255, 255));
      drawList->AddText(
          ImVec2(node.x + additionalWidth,
                 node.y + constants::NODE_HEIGHT / 2 - textParams.y / 2),
          IM_COL32(255, 255, 255, 255), node.name.c_str());
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
  }
}