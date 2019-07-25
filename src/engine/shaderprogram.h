#pragma once
#include "asset.h"
#include <memory>
#include <string>
#include <glad/glad.h>


namespace Engine {
namespace Assets {
enum ShaderType {
  SHADER_TYPE_VERTEX = GL_VERTEX_SHADER,
  SHADER_TYPE_GEOMETRY = GL_GEOMETRY_SHADER,
  SHADER_TYPE_FRAGMENT = GL_FRAGMENT_SHADER
};
  
class ShaderProgram : public Asset {
 public:
  ShaderProgram(std::string name, std::vector<std::string> flags, std::string path) : Asset(name, flags, path, SHADER_PROGRAM_VERT_FRAG),
                                                                                      glID{0} {};
  
  ~ShaderProgram() { release(); }

  virtual void load() override;
  virtual void release() override;

  void bind() const;
  void unbind() const;
  GLuint getGLID() const;

 private:
  GLuint glID;
  
  GLuint compileShader(const std::string& source, ShaderType type);
  void linkProgram(GLuint vShader, GLuint fShader);
};
} // namespace Assets
} // namespace Engine
