#pragma once
#include "asset.h"
#include <memory>

namespace Engine {
namespace Assets {
const std::map<std::string, AssetType> manifestTypeToEnum = {
    {"SHADEVF", SHADER_PROGRAM_VERT_FRAG}, {"MESH", MESH}};

class AssetManager {
 private:
  std::string ASSET_DIR;

  std::string manifestContents;
  // TODO: It's incredibly inefficient to load every (even uninitialized) Asset
  // object into memory, like, do better
  std::vector<Asset *> assetPool;

  void buildAsset(std::string &type, std::string &filename,
                  std::string &assetname, std::vector<std::string> &flags);
  void constructMesh(std::string &filename, std::string &assetname,
                     std::vector<std::string> &flags);
  void constructShaderProgram(std::string &filename, std::string &assetname,
                              std::vector<std::string> &flags);

 public:
  AssetManager() : ASSET_DIR{"./assets/"}, manifestContents{""}, assetPool{std::vector<Asset *>()} {};;
  ~AssetManager();

  void parseManifest();

  template<class T>
  std::vector<T *> getAssets(std::vector<std::string> flags, bool matchAll);

  template<class T>
  std::vector<T *> getAssets(std::string name);
};

template<class T>
inline std::vector<T *> AssetManager::getAssets(std::vector<std::string> flags,
                                                bool matchAll) {
  std::vector<T *> container;

  for (auto a : assetPool) {
    if (a->flags == flags && matchAll) {
      container.push_back(static_cast<T *>(a));
      continue;
    }

    for (auto af : a->flags) {
      for (auto rf : flags) {
        if (af == rf) {
          container.push_back(static_cast<T *>(a));
        }
      }
    }
  }

  return container;
}

template<class T>
inline std::vector<T *> AssetManager::getAssets(std::string name) {
  std::vector<T *> container;

  for (auto a : assetPool) {
    if (a->name == name) {
      container.push_back(static_cast<T *>(a));
    }
  }

  return container;
}

} // namespace Assets
} // namespace Engine
