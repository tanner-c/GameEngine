#include "assetmanager.h"
#include "io.h"
#include "mesh.h"
#include "shader.h"
#include "shaderprogram.h"
#include <sstream>

using namespace Engine::Assets;
using namespace Utility::IO;

void AssetManager::buildAsset(std::string &type, std::string &filename,
                              std::string &assetname,
                              std::vector<std::string> &flags) {
  AssetType t;

  try {
    t = manifestTypeToEnum.at(type);
  }
  catch (std::exception err) {
    // TODO: Un-Applefy/Generify this message
    Logger::instance().log(LOG_SEVERITY_FATAL,
                           "Unable to properly parse manifest file. Please "
                           "check syntax and try again.");
  }

  switch (t) {
    case SHADER_PROGRAM_VERT_FRAG:
      // TODO: It might be a good idea to write a class that represents a file
      // path
      constructShaderProgram(filename, assetname, flags);
      return;

    case MESH:constructMesh(filename, assetname, flags);
      return;
  }
}

void AssetManager::constructMesh(std::string &filename, std::string &assetname,
                                 std::vector<std::string> &flags) {

  std::string meshPath = ASSET_DIR;

  meshPath.append(MESH_DIR);
  meshPath.append("/");
  meshPath.append(filename);
  meshPath.append(MESH_EXT);

  Asset *mesh = new Mesh(assetname, flags, meshPath, MESH);

  assetPool.push_back(mesh);
}

void AssetManager::constructShaderProgram(std::string &filename,
                                          std::string &assetname,
                                          std::vector<std::string> &flags) {
  std::string shaderPath = ASSET_DIR;

  shaderPath.append(SHADER_DIR);
  shaderPath.append("/");
  shaderPath.append(filename);

  auto vShader = new VertexShader(shaderPath + VERTEX_SHADER_EXT);
  auto fShader = new FragmentShader(shaderPath + FRAGMENT_SHADER_EXT);

  Asset *program =
      new ShaderProgram(assetname, flags, shaderPath, vShader, fShader);

  assetPool.push_back(program);
}

AssetManager::~AssetManager() {
  for (auto e : assetPool) {
    delete e;
  }
}

// TODO: This can likely be made better and prettier. What's a parser?
void AssetManager::parseManifest() {
  manifestContents = readFile(std::string(ASSET_DIR) + MANIFEST_FILE);

  std::stringstream buffer(manifestContents);

  // TODO: Add flag validation?
  std::vector<std::string> flags;

  std::vector<std::string> tokens;

  try {
    for (std::string line; std::getline(buffer, line);) {
      if (line.empty()) {
        continue;
      } else if (line.at(0) == '#') {
        continue;
      }

      tokens = tokenizeString(line, ' ');

      if (tokens.size() == 4) {
        std::string strflags = tokens.at(3);

        if (strflags.find(',') != std::string::npos) {
          auto tokflags = tokenizeString(strflags, ',');
          flags.insert(flags.end(), tokflags.begin(), tokflags.end());
        }
      } else {
        // TODO: Un-Applefy/Generify this message
        Logger::instance().log(LOG_SEVERITY_FATAL,
                               "Unable to properly parse manifest file. Please "
                               "check syntax and try again.");
      }

      buildAsset(tokens.at(0), tokens.at(1), tokens.at(2), flags);
    }
  }
  catch (std::exception err) {
    // TODO: Un-Applefy/Generify this message
    Logger::instance().log(LOG_SEVERITY_FATAL,
                           "Unable to properly parse manifest file. Please "
                           "check syntax and try again.");
  }
}
