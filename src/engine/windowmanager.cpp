#include "windowmanager.h"
#include <exception>

using namespace Utility::IO;
using namespace Engine;

WindowManager::WindowManager(int sizeX, int sizeY, bool fullscreen,
                             std::string title) {
  WindowConfig wc = {};

  auto winSize = glm::vec2();

  winSize.x = (float) sizeX;
  winSize.y = (float) sizeY;

  wc.windowSize = winSize;
  wc.fullscreen = fullscreen;
  wc.title = title;

  // TODO: Allow configurable monitor selection
  if (fullscreen) {
    wc.displayMonitor = glfwGetPrimaryMonitor();
  } else {
    wc.displayMonitor = NULL;
  }

  wc.window = nullptr;

  winConfig = wc;
}

WindowManager::~WindowManager() { glfwDestroyWindow(winConfig.window); }

WindowConfig WindowManager::getWindowConfig() { return winConfig; }

void WindowManager::createWindowAndContext() {
  if (winConfig.window != nullptr) {
    Logger::instance().log(LOG_SEVERITY_FATAL, "Additional call to createWindowAndContext(). There can only be one!");
  }

  winConfig.window =
      glfwCreateWindow((int) winConfig.windowSize.x,
                       (int) winConfig.windowSize.y,
                       winConfig.title.c_str(),
                       winConfig.displayMonitor, NULL);
}

void WindowManager::swap() {
  glfwSwapBuffers(winConfig.window);
  
}

glm::vec2 WindowManager::getWindowSize() {
  return this->winConfig.windowSize;
  
}

bool WindowManager::pollEvents() {
  glfwPollEvents();
  return glfwWindowShouldClose(winConfig.window);
}

bool WindowManager::getIsFullscreen() {
  return winConfig.fullscreen;
}

void WindowManager::setIsFullscreen(bool fullscreen) {
  // TODO: Implement
}
