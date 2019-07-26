#pragma once
#include "engine/scene/sceneobject.h"
#include "engine/graphics/renderable.h"
#include "engine/assets/mesh.h"


namespace Engine {
namespace Scene {
namespace Components {
class CameraComponent;
  
class MeshComponent : public SceneObjectComponent, public Graphics::Renderable {
public:
  std::unique_ptr<Assets::Mesh> mesh;
  
  MeshComponent() : SceneObjectComponent() {};
  
  virtual void draw() override;
  virtual void start() override;
  virtual void instantiated(SceneObject* parent) override;
  
private:
  void acquireRenderCamera();
  
  CameraComponent* renderCamera;
  
};
}
} // namespace Scene
} // namespace Engine
