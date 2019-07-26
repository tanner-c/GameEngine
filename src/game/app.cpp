#include "app.h"
#include "engine/scene/scene.h"
#include "engine/scene/meshcomponent.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace Utility::IO;
using namespace Game;

App::App() : active{false} {
  //glfwSetErrorCallback(&glfwError);

  glfwInit();

  // TODO: Don't have hardcoded values for window config
  assetManager = new Assets::AssetManager();
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

void App::init() {
  active = true;

  assetManager->parseManifest();
  pipeline->configGLContext();
  windowManager->createWindowAndContext();
  pipeline->initGL();
  pipeline->precompileShaders();
  
  // TODO: Test code, please remove
  auto s = Engine::Scene::Scene::newScene();
  auto so = new Engine::Scene::SceneObject();
  
  so->name = "suzanne";
  so->attachComponent<Engine::Scene::Components::MeshComponent>();
  
  s->addSceneObject(so);
  
  s->start();
}

void App::render() {
  pipeline->draw();
  windowManager->swap();
  active = !windowManager->pollEvents();
}

void App::programArgs(int argc, char *argv[]) {
  for (int i = 1; i < (argc); i++) {
    std::string a(argv[i]);
    
    if (a.find("--") != std::string::npos) {
      auto b = a.substr(2, a.length() - 2);
      std::string c;
      
      if ((i + 1) <= argc) {
        i++;
        c = argv[i];
        args[b] = c;
        continue;
      } else {
        args[b] = "";
      }
    }
  }
}

void App::tick() {
  Engine::Scene::Scene::currentScene->tick();
}

bool App::isActive() {
  return active;
}
