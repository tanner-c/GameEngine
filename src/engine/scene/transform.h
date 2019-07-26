#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Engine {
namespace Scene {
  class Transform {
  public:
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
    
    Transform() : Transform(glm::vec3(),
                            glm::vec3(),
                            glm::vec3()) {};
    Transform(glm::vec3 translation) : Transform(translation,
                                                 glm::vec3(),
                                                 glm::vec3()) {};
    Transform(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale) : translation{translation},
                                                                            rotation{rotation},
                                                                            scale{scale} {};
    
    glm::mat4 matrix() {
      auto t = glm::translate(glm::mat4(), translation);
      auto s = glm::scale(glm::mat4(), scale);
      
      // TODO: add rotation
      glm::mat4 r(1.f);
      
      return t * r * s;
    };
  };
} // namespace Scene
} // namespace Engine
