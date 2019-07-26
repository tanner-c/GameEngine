#pragma once
#include <vector>
#include <string>
#include <memory>

#include "engine/scene/transform.h"
#include <glm/glm.hpp>

namespace Engine {
namespace Scene {

class Scene;
class SceneObject;

class SceneObjectComponent {
public:
  SceneObject* sceneObject;
  
  SceneObjectComponent() : sceneObject { nullptr } {};
  
  virtual void instantiated(SceneObject* parent) = 0;
  virtual void start() {};
  virtual void draw() {};
  virtual void tick() {};
  virtual void end() {};
};


class SceneObject {
public:
  std::string name;
  Transform transform;
  SceneObject* parent;
  Scene* scene;
  
public:
  SceneObject() : SceneObject(Transform()) {};
  SceneObject(glm::vec3 translation) : SceneObject(Transform(translation)) {};
  SceneObject(Transform transform) : transform{transform} {};
  
  template <class T>
  T* getComponent();
  
  template <class T>
  T* attachComponent();
  
  template <class T>
  void detachComponent();
  
  void start() {
    notify(components, [](SceneObjectComponent* c) {
      c->start();
    });
    
    notify(children, [](SceneObject* o) {
      o->start();
    });
  };
  
  void tick() {
    notify(components, [](SceneObjectComponent* c) {
      c->tick();
    });
    
    notify(children, [](SceneObject* o) {
      o->tick();
    });
  };
  
  void draw() {
    notify(components, [](SceneObjectComponent* c) {
      c->draw();
    });
    
    notify(children, [](SceneObject* o) {
      o->draw();
    });
  };
  
  void end() {
    notify(components, [](SceneObjectComponent* c) {
      c->end();
    });
    
    notify(children, [](SceneObject* o) {
      o->end();
    });
  };
  
private:
  std::vector<std::unique_ptr<SceneObjectComponent>> components;
  std::vector<std::unique_ptr<SceneObject>> children;
  
  template <class V, class L>
  void notify(std::vector<V>& vector, L&& lambda);
};
  
template <class V, class L>
inline void SceneObject::notify(std::vector<V>& vector, L&& lambda) {
  if (!vector.empty()) {
    for (int i = 0; i < vector.size(); i++) {
      auto o = vector[i].get();
      
      lambda(o);
    }
  }
}

template <class T>
inline T* SceneObject::getComponent() {
  // This is likely inefficient and done a better way
  T* t = nullptr;
  
  for (int i  = 0; i < components.size(); i++) {
    auto c = components[i].get();
    t = dynamic_cast<T*>(c);
    
    if (t) {
      return t;
    }
  }
  
  return nullptr;
}

template <class T>
inline T* SceneObject::attachComponent() {
  // TODO: Find a better way to check if the component is unique
  if(getComponent<T>()) {
    return nullptr;
  }
  
  auto c = new T();
  
  SceneObjectComponent* soc = dynamic_cast<SceneObjectComponent*>(c);
  
  if(soc) {
    soc->instantiated(this);
    components.push_back(std::unique_ptr<SceneObjectComponent>(soc));
    return c;
  } else {
    return nullptr;
  }
}

template <class T>
inline void SceneObject::detachComponent() {
  SceneObjectComponent* soc = nullptr;
  
  for (auto it = components.begin(); it != components.end(); ++it) {
    soc = dynamic_cast<T*>(it->get());
    
    if (soc) {
      components.erase(it);
      delete soc;
      return;
    }
  }
}
  
} // namespace Scene
} // namespace Engine
