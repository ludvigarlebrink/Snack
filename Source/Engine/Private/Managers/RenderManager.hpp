#pragma once

#include "Managers/IRenderManager.hpp"

#include <set>

namespace snack
{
class RenderManager final : public IRenderManager
{
public:

    RenderManager();

    ~RenderManager();

    RenderWindow* GetRenderWindow() override;

    Transform* PickMesh(const glm::vec3& origin, const glm::vec3& direction) override;

    void RenderSceneToTexture(Framebuffer* framebuffer, int32 width, int32 height) override;

    void RenderSceneCustomCamera(const glm::mat4& viewProjection) override;

protected:

    void DeregisterCameraComponent(CameraComponent* cameraComponent) override;

    void DeregisterDirectionalLightComponent(DirectionalLightComponent* directionalLightComponent) override;

    void DeregisterJointComponent(JointComponent* jointComponent) override;

    void DeregisterMeshComponent(MeshComponent* meshComponent) override;

    void DeregisterPointLightComponent(PointLightComponent* pointLightComponent) override;

    void DeregisterSkinnedMeshComponent(SkinnedMeshComponent* skinnedMeshComponent) override;

    void DeregisterSpotlightComponent(SpotlightComponent* spotlightComponent) override;

    void DeregisterTerrainComponent(TerrainComponent* terrainComponent) override;

    void RegisterCameraComponent(CameraComponent* cameraComponent) override;

    void RegisterDirectionalLightComponent(DirectionalLightComponent* directionalLightComponent) override;

    void RegisterJointComponent(JointComponent* jointComponent) override;

    void RegisterMeshComponent(MeshComponent* meshComponent) override;

    void RegisterPointLightComponent(PointLightComponent* pointLightComponent) override;

    void RegisterSkinnedMeshComponent(SkinnedMeshComponent* skinnedMeshComponent) override;

    void RegisterSpotlightComponent(SpotlightComponent* spotlightComponent) override;

    void RegisterTerrainComponent(TerrainComponent* terrainComponent) override;

private:

    void DeferredGeometryPass(CameraComponent* camera);

    void DeferredLightingPass(CameraComponent* camera);

    void ForwardPass(CameraComponent* camera);

    void RenderToShadowMap(DirectionalLightComponent* light);

    void SetUp();

    void TearDown();

private:

    RenderWindow* m_renderWindow;
    Shader* m_meshShader;
    Shader* m_skinnedMeshShader;
    Shader* m_terrainShader;

    Shader* m_pbrShader;

    Framebuffer* m_deferredFrameBuffer;
    Renderbuffer* m_depthStencil;
    Texture* m_gAlbedo;
    Texture* m_gNormal;
    Texture* m_gPosition;
    Texture* m_gMRA;
    Shader* m_geometryPassShader;
    Shader* m_lightingPassShader;
    FullScreenQuad* m_fullScreenQuad;

    Framebuffer* m_shadowMapFrameBuffer;
    Texture* m_shadowMap;
    Shader* m_depthShader;
    int m_shadowWidth = 1024, m_shadowHeight = 1024;

    std::set<CameraComponent*> m_cameraComponents;
    std::set<DirectionalLightComponent*> m_directionalLightComponents;
    std::set<JointComponent*> m_jointComponents;
    std::set<MeshComponent*> m_meshComponents;
    std::set<PointLightComponent*> m_pointLightComponents;
    std::set<SkinnedMeshComponent*> m_skinnedMeshComponents;
    std::set<SpotlightComponent*> m_spotlightComponents;
    std::set<TerrainComponent*> m_terrainComponents;
};
} // namespace snack
