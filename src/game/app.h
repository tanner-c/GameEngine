#pragma once
#include "engine/assets/assetmanager.h"
#include "engine/graphics/gfxpipeline.h"
#include "engine/utilities/windowmanager.h"
#include <memory>
#include <sstream>

using namespace Engine;

namespace Game {
class App {
 protected:
  bool active;

 public:
  std::map<std::string, std::string> args;

  GFXPipeline *pipeline;
  WindowManager *windowManager;
  Assets::AssetManager *assetManager;

 public:
  ~App();
  App(const App &) = delete;
  App &operator=(const App &) = delete;
  static App &instance();

  void init();
  void tick();
  void render();
  
  void programArgs(int argc, char *argv[]);

  bool isActive();

 private:
  App();
};
} // namespace Game
