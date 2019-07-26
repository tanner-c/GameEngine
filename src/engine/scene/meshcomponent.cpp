#include "scene/meshcomponent.h"
#include "game/app.h"
#include "globals.glsl"
#include "scene/scene.h"
#include "scene/cameracomponent.h"

using namespace Engine::Scene::Components;

void MeshComponent::instantiated(SceneObject* parent) {
  sceneObject = parent;
  
  mesh = std::unique_ptr<Assets::Mesh>(Game::App::instance().assetManager->getAssets<Assets::Mesh>("suzanne")[0]);
  shader = std::unique_ptr<Assets::ShaderProgram>(Game::App::instance().assetManager->getAssets<Assets::ShaderProgram>("standard")[0]);
}

void MeshComponent::start() {
  if (!mesh || !shader) { return; }
  
  mesh->load();
  shader->load();
  
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);
  
  glGenBuffers(1, &vboID);
  glGenBuffers(1, &iboID);
  
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
  
  glBufferData(GL_ARRAY_BUFFER, mesh->meshData.vertices.size() * sizeof(glm::vec3),
               &mesh->meshData.vertices[0], GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->meshData.vertIndices.size() * sizeof(int),
               &mesh->meshData.vertices[0], GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  
  acquireRenderCamera();
}

void MeshComponent::acquireRenderCamera() {
  // TODO: This needs to be called at runtime if the camera changes
  renderCamera = sceneObject->scene->mainCamera->getComponent<CameraComponent>();
}

void MeshComponent::draw() {
  shader->bind();
  glBindVertexArray(vaoID);
  glEnableVertexAttribArray(POSITION_ATTRIB_LOCATION);
  
  auto mvp = renderCamera->getViewProjectionMatrix() * sceneObject->transform.matrix();
  auto uniform_loc = glGetUniformLocation(shader->getGLID(), "MVP");
  
  glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, &mvp[0][0]);
  glDrawElements(GL_TRIANGLES, mesh->meshData.vertIndices.size(), GL_UNSIGNED_INT, 0);
}
