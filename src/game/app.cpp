#include "app.h"
#include "engine/mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace Utility::IO;
using namespace Game;

App::App()
    : active{false} {
  glfwSetErrorCallback(&glfwError);

  glfwInit();

  // TODO: Don't have hardcoded values for window config
  assetManager = new AssetManager();
  windowManager = new WindowManager(800, 600, false, "OpenGLSandbox");
  pipeline = new GFXPipeline();
}

App::~App() {
  delete windowManager;
  delete pipeline;

  glfwTerminate();
}

App &App::instance() {
  static App a;
  return a;
}

void App::begin() {
  active = true;

  assetManager->parseManifest();
  pipeline->configGLContext();
  windowManager->createWindowAndContext();
  pipeline->initGL();
  pipeline->precompileShaders();
}

void App::render() {
  pipeline->draw();
  windowManager->swap();
  active = !windowManager->pollEvents();
}

void App::tick() {}

bool App::isActive() { return active; }