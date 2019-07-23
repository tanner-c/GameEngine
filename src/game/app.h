#pragma once
#include "engine/assetmanager.h"
#include "engine/gfxpipeline.h"
#include "engine/windowmanager.h"
#include <memory>
#include <sstream>

using namespace Engine::Assets;
using namespace Engine;

namespace Game {
class App {
 protected:
  bool active;

 public:
  GFXPipeline *pipeline;
  WindowManager *windowManager;
  AssetManager *assetManager;

 public:
  ~App();
  App(const App &) = delete;
  App &operator=(const App &) = delete;
  static App &instance();

  void begin();
  void tick();
  void render();

  bool isActive();

 private:
  App();
};
} // namespace Game