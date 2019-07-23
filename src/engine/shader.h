#pragma once
#include <string>
#define GLEW_STATIC
#include "io.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

using namespace Utility::IO;

namespace Engine {
namespace Assets {
enum ShaderType {
  SHADER_TYPE_VERTEX = GL_VERTEX_SHADER,
  SHADER_TYPE_GEOMETRY = GL_GEOMETRY_SHADER,
  SHADER_TYPE_FRAGMENT = GL_FRAGMENT_SHADER
};

class Shader {
 protected:
  GLuint glID;
  bool compiled;
  ShaderType type;

 public:
  const std::string source;
  const std::string path;

  Shader(std::string filePath)
      : type{SHADER_TYPE_VERTEX}, glID{0}, compiled{false}, path{filePath},
        source{readFile(filePath)} {};
  ~Shader();

  void compile();
  bool isCompiled() const;

  GLuint getGLID() const;
};

class VertexShader : public Shader {
 public:
  VertexShader(std::string filePath)
      : Shader(filePath) {
    type = SHADER_TYPE_VERTEX;
  };
};

class FragmentShader : public Shader {
 public:
  FragmentShader(std::string filePath)
      : Shader(filePath) {
    type = SHADER_TYPE_FRAGMENT;
  };
};
} // namespace Assets
} // namespace Engine