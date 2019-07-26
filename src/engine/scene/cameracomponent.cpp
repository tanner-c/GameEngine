#include "scene/cameracomponent.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Engine::Scene::Components;


void CameraComponent::instantiated(SceneObject *parent) {
  sceneObject = parent;
}

glm::mat4 CameraComponent::getViewProjectionMatrix() {
  return getProjectionMatrix() * sceneObject->transform.matrix();
}

glm::mat4 CameraComponent::getProjectionMatrix() {
  // TODO: hardcoded values
  return glm::perspective(glm::radians(45.f), 4.f / 3.f, 0.1f, 100.f);
}
