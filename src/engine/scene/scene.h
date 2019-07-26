#pragma once
#include <map>
#include <string>
#include <memory>
#include "engine/scene/sceneobject.h"

namespace Engine {
namespace Scene {
  
class Scene {
public:
  static std::unique_ptr<Scene> currentScene;
  static Scene* newScene();
  SceneObject* mainCamera;
  
  void start();
  void tick();
  void draw();
  void end();
  
  SceneObject* getSceneObjectByName(std::string name);
  void addSceneObject(SceneObject* so);
  
private:
  std::map<std::string, std::unique_ptr<SceneObject>> sceneObjects;
  
  Scene() {};
  
  template <class A, class B, class L>
  void notify(std::map<A, B>& map, L&& lambda);
};
  
template <class A, class B, class L>
void Scene::notify(std::map<A, B>& map, L&& lambda) {
  if (!map.empty()) {
    for (auto &x : map) {
      lambda(x.second.get());
    }
  }
}
  
} // namespace Scene
} // namespace Engine
