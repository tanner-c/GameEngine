#pragma once
#include "engine/scene/sceneobject.h"
#include <glm/glm.hpp>

namespace Engine {
namespace Scene {
namespace Components {
  
  class CameraComponent : public SceneObjectComponent {
  public:
    
    virtual void instantiated(SceneObject* parent) override;
    
    glm::mat4 getViewProjectionMatrix();
    
  private:
    glm::mat4 getProjectionMatrix();
    
  };
  
}
}
}
