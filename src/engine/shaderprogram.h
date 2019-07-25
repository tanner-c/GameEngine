#pragma once
#include "asset.h"
#include "shader.h"
#include <memory>
#include <string>
#include <glad/glad.h>


namespace Engine {
namespace Assets {
class ShaderProgram : public Asset {
 public:
  std::unique_ptr<VertexShader> vShader;
  std::unique_ptr<FragmentShader> fShader;

 public:
  ShaderProgram(std::string name, std::vector<std::string> flags,
                std::string path, VertexShader *vShader,
                FragmentShader *fShader)
      : glID{0}, vShader{vShader}, fShader{fShader},
        Asset(name, flags, path, SHADER_PROGRAM_VERT_FRAG) {};
  ~ShaderProgram() { release(); }

  virtual void load() override;
  virtual void release() override;

  void bind() const;
  void unbind() const;
  GLuint getGLID() const;

 private:
  GLuint glID;
};
} // namespace Assets
} // namespace Engine