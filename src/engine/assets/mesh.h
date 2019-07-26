#pragma once
#include "asset.h"
#include <memory>
#include <glm/glm.hpp>

namespace Engine {
namespace Assets {
struct MeshData {
  std::vector<glm::vec4> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;

  std::vector<int> vertIndices;
  std::vector<int> uvIndices;
  std::vector<int> normalIndices;
};
  
class Mesh : public Asset {
 public:
  MeshData meshData;
  
  Mesh(std::string name, std::vector<std::string> flags, std::string path, AssetType type) : Asset(name, flags, path, type) {};

  virtual void load() override;
  virtual void release() override;
};
} // namespace Assets
} // namespace Engine
