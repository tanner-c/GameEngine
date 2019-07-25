#include "mesh.h"
#include "utilities/io.h"
#include <sstream>

using namespace Engine::Assets;
using namespace Utility::IO;

// TODO: This likely needs to be under Utility::IO
void Mesh::parseObj(std::stringstream &fileStream) {
  for (std::string line; std::getline(fileStream, line);) {
    if (line.at(0) == '#' || line.empty()) {
      continue;
    }

    auto tokens = tokenizeString(line, ' ');

    if (tokens.empty()) {
      continue;
    } else if (tokens.at(0) == "v" &&
        (tokens.size() == 4 || tokens.size() == 5)) {
      // Vertex definition, contains X Y Z and optional W coordinate
      // If token size is 4 then it is only providing us X Y and Z

      glm::vec4 vertex;

      vertex.x = std::stof(tokens.at(1));
      vertex.y = std::stof(tokens.at(2));
      vertex.z = std::stof(tokens.at(3));

      if (tokens.size() == 5) {
        vertex.w = std::stof(tokens.at(4));
      } else {
        vertex.w = 1;
      }

      vertices.push_back(vertex);
    } else if (tokens.at(0) == "vt" &&
        (tokens.size() == 3 || tokens.size() == 4)) {
      // UV coordinate definition, contains U and optional V and W coordinates
      // This engine only supports 2D textures, if the definition only contains
      // 1 coordinate we will ignore it entirely If the definition contains 3
      // coordinates, we will ignore the third

      glm::vec2 uv;

      uv.x = std::stof(tokens.at(1));
      uv.y = std::stof(tokens.at(2));

      uvs.push_back(uv);
    } else if (tokens.at(0) == "vn" && tokens.size() == 4) {
      // Normal defintion, always contains X Y and Z coordinates

      glm::vec3 normal;

      normal.x = std::stof(tokens.at(1));
      normal.y = std::stof(tokens.at(2));
      normal.z = std::stof(tokens.at(3));

      normals.push_back(normal);
    } else if (tokens.at(0) == "f") {
      // Face definition, this type of definition can take many different forms
      // It may simply contain a list of vertices to define a face separated by
      // spaces Or it may contain texture and UV coordinates as well, separated
      // by forward slashes If we detect this, we will do an additional split to
      // grab that information as well

      // We do not to a size() comparison for tokens here because "faces" can
      // have many vertices

      // This can be used for indexing purposes in OpenGL and can negate the
      // need to Index our own VBOs

      for (int i = 1; i < tokens.size(); i++) {

        // If only a vertex and normal index is defined
        // We do this comparison first because the following comparison will
        // always return true on these
        if (tokens.at(i).find("//") != std::string::npos) {
          auto indices = tokenizeString(tokens.at(i), '/');

          vertIndices.push_back(std::stoi(indices.at(0)) - 1);
          normalIndices.push_back(std::stoi(indices.at(1)) - 1);

        } else if (tokens.at(i).find("/") != std::string::npos) {
          // If all three indices are defined
          auto indices = tokenizeString(tokens.at(i), '/');

          vertIndices.push_back(std::stoi(indices.at(0)) - 1);
          uvIndices.push_back(std::stoi(indices.at(1)) - 1);
          normalIndices.push_back(std::stoi(indices.at(2)) - 1);

        } else {
          // Only vertex indices are defined
          vertIndices.push_back(std::stoi(tokens.at(i)) - 1);
        }
      }
    }
  }
}

void Mesh::load() {
  std::stringstream fileContents(readFile(path));

  // TODO: Un-Applefy/Generify this message
  // TODO: This doesn't need to be a fatal error
  try {
    parseObj(fileContents);
  }
  catch (std::exception e) {
    Logger::instance().log(LOG_SEVERITY_FATAL,
                           std::string("Failed to parse OBJ file at: ") + path);
  }

  // TODO: Revisit this after determining the handling of shaders and
  // gameobjects and such
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);

  glGenBuffers(1, &vboID);
  glGenBuffers(1, &iboID);

  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
               &vertices[0], GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertIndices.size() * sizeof(int),
               &vertIndices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::release() {}

void Mesh::draw(const ShaderProgram *shader,
                const glm::mat4 &matViewProjection) {
  // TODO: Revisit this as well, this class and ShaderProgram need refactoring
  glBindVertexArray(vaoID);
  glEnableVertexAttribArray(0);
  shader->bind();

  auto modelLocation = glGetUniformLocation(shader->getGLID(), "matModel");
  auto viewProjectionLocation =
      glGetUniformLocation(shader->getGLID(), "matViewProjection");
  auto colorLocation = glGetUniformLocation(shader->getGLID(), "color");

  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &transform.getMatrix()[0][0]);
  glUniformMatrix4fv(viewProjectionLocation, 1, GL_FALSE, &matViewProjection[0][0]);
  glUniform4f(colorLocation, 1.f, 1.f, 1.f, 1.f);

  glDrawElements(GL_TRIANGLES, vertIndices.size(), GL_UNSIGNED_INT, 0);

  shader->unbind();
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}
