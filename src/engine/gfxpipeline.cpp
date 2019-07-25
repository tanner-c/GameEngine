#include "gfxpipeline.h"
#include "game/app.h"
#include "shaderprogram.h"
#include "mesh.h"

using namespace Utility::IO;
using namespace Engine::Assets;
using namespace Game;

void GFXPipeline::configGLContext() {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
}

void GFXPipeline::initGL() {
  glfwMakeContextCurrent(
      App::instance().windowManager->getWindowConfig().window);

  if (!gladLoadGL()) {
    Logger::instance().log(LOG_SEVERITY_FATAL, "Unable to initialize glad!");
  }

  auto msg = std::stringstream()
             << "Initialized OpenGL context version: " << GLVersion.major << "."
             << GLVersion.minor;

  Logger::instance().log(LOG_SEVERITY_NORMAL, msg.str());

  glClearColor(1, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void GFXPipeline::draw() {
  // TODO: Test code, please remove
  static Mesh *myCube = nullptr;
  static ShaderProgram *myShader = nullptr;

  if (myCube == nullptr || myShader == nullptr) {
    myCube = App::instance().assetManager->getAssets<Mesh>("suzanne")[0];
    myShader =
        App::instance().assetManager->getAssets<ShaderProgram>("standard")[0];

    myCube->load();
    myShader->load();
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  myCube->draw(myShader, (projection * view));
}

void GFXPipeline::precompileShaders() {
  std::vector<ShaderProgram *> shaders =
      App::instance().assetManager->getAssets<ShaderProgram>({"precompile"},
                                                             false);

  for (auto s : shaders) {
    s->load();
  }
}
