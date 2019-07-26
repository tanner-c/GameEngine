#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
class GFXPipeline {

 public:
  // TODO: hardcoded values
  GFXPipeline() {}

  void configGLContext();
  void initGL();
  void draw();

  void precompileShaders();
};
} // namespace Engine
