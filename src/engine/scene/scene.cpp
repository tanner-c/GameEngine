#include "scene/scene.h"
#include "scene/sceneobject.h"
#include "scene/cameracomponent.h"

using namespace Engine::Scene;

std::unique_ptr<Scene> Scene::currentScene;

Scene* Scene::newScene() {
  auto s = new Scene();
  
  if (Scene::currentScene) {
    Scene::currentScene->end();
  }
  
  auto c = new SceneObject();
  
  c->attachComponent<Components::CameraComponent>();
  s->addSceneObject(c);
  
  s->mainCamera = c;
  
  Scene::currentScene = std::unique_ptr<Scene>(s);
  
  return s;
}

void Scene::start() {
  notify(sceneObjects, [](SceneObject* so) {
    so->start();
  });
}

void Scene::tick() {
  notify(sceneObjects, [](SceneObject* so) {
    so->tick();
  });
}

void Scene::draw() {
  notify(sceneObjects, [](SceneObject* so) {
    so->draw();
  });
}

void Scene::end() {
  notify(sceneObjects, [](SceneObject* so) {
    so->end();
  });
}

SceneObject* Scene::getSceneObjectByName(std::string name) {
  try {
    return sceneObjects.at(name).get();
  } catch (std::out_of_range) {
    return nullptr;
  }
}

void Scene::addSceneObject(SceneObject* so) {
  if (so) {
    so->scene = this;
    sceneObjects.insert(std::pair<std::string, std::unique_ptr<SceneObject>>(so->name, std::unique_ptr<SceneObject>(so)));
  }
}
