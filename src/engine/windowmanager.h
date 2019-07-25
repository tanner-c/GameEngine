#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <string>
#include "io.h"

namespace Engine {
struct WindowConfig {
  glm::vec2 windowSize;
  bool fullscreen;
  std::string title;

  GLFWmonitor *displayMonitor;
  GLFWwindow *window;

  WindowConfig()
      : windowSize{glm::vec2(800, 600)}, fullscreen{false}, title{"No title"},
        displayMonitor{nullptr}, window{nullptr} {};
};

class WindowManager {
 protected:
  WindowConfig winConfig;

 public:
  WindowManager(int sizeX, int sizeY, bool fullscreen, std::string string);

  ~WindowManager();

  WindowConfig getWindowConfig();

  void createWindowAndContext();
  void swap();

  glm::vec2 getWindowSize();

  bool pollEvents();

  bool getIsFullscreen();
  void setIsFullscreen(bool fullscreen);

 protected:
};
} // namespace Engine