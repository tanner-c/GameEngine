#pragma once
#include "asset.h"
#include "shaderprogram.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

namespace Engine {
namespace Assets {
// TODO: This would likely fit better elsewhere

struct Transform {
  Transform() : matTranslation{glm::mat4(1.f)},
                matRotation{glm::mat4(1.f)},
                matScale{glm::mat4(1.f)} {};

  glm::mat4 getMatrix() {
    return matTranslation * matRotation * matScale;
  }

  void translate(glm::vec3 vector) {
    matTranslation = glm::translate(matTranslation, vector);
  }

  void scale(glm::vec3 vector) {
    matScale = glm::scale(vector);
  }

 private:
  glm::mat4 matTranslation;
  glm::mat4 matRotation;
  glm::mat4 matScale;
};

class Mesh : public Asset {
  // TODO: Privatize these after implementing scene & objects
 public:
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;

  std::vector<int> vertIndices;
  std::vector<int> uvIndices;
  std::vector<int> normalIndices;

  GLuint vaoID;
  GLuint vboID;
  GLuint iboID;

  void parseObj(std::stringstream &fileStream);

 public:
  // TODO: These need to be exported to gameobject/material/something code after testing
  Transform transform;

  Mesh(std::string name, std::vector<std::string> flags, std::string path, AssetType type) : Asset(name, flags, path, type),
                                                                                             vertices{std::vector<glm::vec3>()},
                                                                                             uvs{std::vector<glm::vec2>()},
                                                                                             normals{std::vector<glm::vec3>()} {};

  virtual void load() override;
  virtual void release() override;

  void draw(const ShaderProgram *shader, const glm::mat4 &matViewProjection);

};
} // namespace Assets
} // namespace Engine
