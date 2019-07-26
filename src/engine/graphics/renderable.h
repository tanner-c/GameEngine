#pragma once
#include "engine/graphics/shaderprogram.h"
#include <memory>
#include <glad/glad.h>


namespace Engine {
namespace Graphics {
class Renderable {
public:
  // Move this out to a material object that supports textures
  std::unique_ptr<Assets::ShaderProgram> shader;
  
  virtual void draw() = 0;
  
protected:
  GLuint vaoID;
  GLuint vboID;
  GLuint iboID;
};
} // namespace Graphics
} // namespace Engine
