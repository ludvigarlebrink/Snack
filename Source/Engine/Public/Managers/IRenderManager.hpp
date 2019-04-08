#pragma once

#include "BaseTypes.hpp"
#include "RenderCoreForward.hpp"

#include <glm/glm.hpp>

namespace spy
{
class CameraComponent;
class DirectionalLightComponent;
class JointComponent;
class MeshComponent;
class PointLightComponent;
class SkinnedMeshComponent;
class SpotlightComponent;
class Transform;

class ENGINE_API IRenderManager
{
    friend CameraComponent;
    friend DirectionalLightComponent;
    friend JointComponent;
    friend MeshComponent;
    friend PointLightComponent;
    friend SkinnedMeshComponent;
    friend SpotlightComponent;

public:

    virtual ~IRenderManager() = default;

    virtual RenderWindow* GetRenderWindow() = 0;

    virtual Transform* PickMesh(const glm::vec3& direction, const glm::vec3& origin) = 0;

    virtual void RenderScene() = 0;

    virtual void RenderSceneToTexture(const glm::mat4& viewProjection) = 0;

protected:

    virtual void DeregisterCameraComponent(CameraComponent* cameraComponent) = 0;

    virtual void DeregisterDirectionalLightComponent(DirectionalLightComponent* directionalLightComponent) = 0;

    virtual void DeregisterJointComponent(JointComponent* jointComponent) = 0;

    virtual void DeregisterMeshComponent(MeshComponent* meshComponent) = 0;

    virtual void DeregisterPointLightComponent(PointLightComponent* pointLightComponent) = 0;

    virtual void DeregisterSkinnedMeshComponent(SkinnedMeshComponent* skinnedMeshComponent) = 0;

    virtual void DeregisterSpotlightComponent(SpotlightComponent* spotlightComponent) = 0;

    virtual void RegisterCameraComponent(CameraComponent* cameraComponent) = 0;

    virtual void RegisterDirectionalLightComponent(DirectionalLightComponent* directionalLightComponent) = 0;

    virtual void RegisterJointComponent(JointComponent* jointComponent) = 0;

    virtual void RegisterMeshComponent(MeshComponent* meshComponent) = 0;

    virtual void RegisterPointLightComponent(PointLightComponent* pointLightComponent) = 0;

    virtual void RegisterSkinnedMeshComponent(SkinnedMeshComponent* skinnedMeshComponent) = 0;

    virtual void RegisterSpotlightComponent(SpotlightComponent* spotlightComponent) = 0;
};
} // namespace spy
