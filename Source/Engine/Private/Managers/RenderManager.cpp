#include "RenderManager.hpp"
#include "Components/Rendering/CameraComponent.hpp"
#include "Components/Rendering/DirectionalLightComponent.hpp"
#include "Components/Rendering/JointComponent.hpp"
#include "Components/Rendering/MeshComponent.hpp"
#include "Components/Rendering/PointLightComponent.hpp"
#include "Components/Rendering/SkinnedMeshComponent.hpp"
#include "Components/Rendering/SpotlightComponent.hpp"
#include "FileSystem.hpp"
#include "UtilsInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "Transform.hpp"

namespace spy
{
RenderManager::RenderManager()
    : m_renderWindow(nullptr)
{
    SetUp();
}

RenderManager::~RenderManager()
{
    TearDown();
}

RenderWindow* RenderManager::GetRenderWindow()
{
    return m_renderWindow;
}

Transform* RenderManager::PickMesh(const glm::vec3& origin, const glm::vec3& direction)
{
    std::vector<MeshComponent*> hits;
    for (auto meshComponent : m_meshComponents)
    {
        Intersection::RayHitData rayHitData;
        if (Intersection::RayVsSphere(origin, direction, meshComponent->GetTransform()->GetWorldPosition(), meshComponent->GetSphereRadius(), rayHitData))
        {
            return meshComponent->GetTransform();
        }
    }

    return nullptr;
}

void RenderManager::RenderSceneToTexture(Framebuffer* framebuffer)
{
}

void RenderManager::RenderSceneCustomCamera(const glm::mat4& viewProjection)
{
    m_renderWindow->EnableBlend(false);
    m_renderWindow->EnableCullFace(true);
    m_renderWindow->EnableDepthTest(true);

    m_meshShader->Use();
    int32 lightCount = 0;
    for (auto directionalLight : m_directionalLightComponents)
    {
        glm::mat4 model = directionalLight->GetTransform()->GetWorldMatrix();
        m_meshShader->SetVec3Slow("DirectionalLights[" + std::to_string(lightCount) + "].direction", glm::normalize(glm::vec3(-model[0])));
        m_meshShader->SetVec3Slow("DirectionalLights[" + std::to_string(lightCount) + "].color", glm::vec3(1.0f, 1.0f, 1.0f));
        m_meshShader->SetFloatSlow("DirectionalLights[" + std::to_string(lightCount) + "].intensity", 1.0f);
        ++lightCount;
    }
    m_meshShader->SetIntSlow("DirectionalLightCount", lightCount);

    for (auto meshComponent : m_meshComponents)
    {
        Mesh* mesh = meshComponent->GetMesh();
        m_meshShader->SetMat4Slow("Model", meshComponent->GetTransform()->GetWorldMatrix());
        m_meshShader->SetMat4Slow("ViewProjection", viewProjection);
        mesh->Render(Mesh::Mode::TRIANGLES);
    }
}

void RenderManager::DeregisterCameraComponent(CameraComponent* cameraComponent)
{
    m_cameraComponents.erase(cameraComponent);
}

void RenderManager::DeregisterDirectionalLightComponent(DirectionalLightComponent* directionalLightComponent)
{
    m_directionalLightComponents.erase(directionalLightComponent);
}

void RenderManager::DeregisterJointComponent(JointComponent* jointComponent)
{
    m_jointComponents.erase(jointComponent);
}

void RenderManager::DeregisterMeshComponent(MeshComponent* meshComponent)
{
    m_meshComponents.erase(meshComponent);
}

void RenderManager::DeregisterPointLightComponent(PointLightComponent* pointLightComponent)
{
    m_pointLightComponents.erase(pointLightComponent);
}

void RenderManager::DeregisterSkinnedMeshComponent(SkinnedMeshComponent* skinnedMeshComponent)
{
    m_skinnedMeshComponents.erase(skinnedMeshComponent);
}

void RenderManager::DeregisterSpotlightComponent(SpotlightComponent* spotlightComponent)
{
    m_spotlightComponents.erase(spotlightComponent);
}

void RenderManager::RegisterCameraComponent(CameraComponent* cameraComponent)
{
    m_cameraComponents.insert(cameraComponent);
}

void RenderManager::RegisterDirectionalLightComponent(DirectionalLightComponent* directionalLightComponent)
{
    m_directionalLightComponents.insert(directionalLightComponent);
}

void RenderManager::RegisterJointComponent(JointComponent* jointComponent)
{
    m_jointComponents.insert(jointComponent);
}

void RenderManager::RegisterMeshComponent(MeshComponent* meshComponent)
{
    m_meshComponents.insert(meshComponent);
}

void RenderManager::RegisterPointLightComponent(PointLightComponent* pointLightComponent)
{
    m_pointLightComponents.insert(pointLightComponent);
}

void RenderManager::RegisterSkinnedMeshComponent(SkinnedMeshComponent* skinnedMeshComponent)
{
    m_skinnedMeshComponents.insert(skinnedMeshComponent);
}

void RenderManager::RegisterSpotlightComponent(SpotlightComponent* spotlightComponent)
{
    m_spotlightComponents.insert(spotlightComponent);
}

void RenderManager::RenderDeferred(CameraComponent* camera)
{
}

void RenderManager::SetUp()
{
    m_renderWindow = new RenderWindow("Snack Editor", 1280, 720);

    m_meshShader = new Shader();
    m_meshShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/DefaultMesh.vs.glsl"), Shader::Type::VERTEX_SHADER);
    m_meshShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/DefaultMesh.fs.glsl"), Shader::Type::FRAGMENT_SHADER);
    m_meshShader->LinkProgram();

    // Deferred rendering.
    m_deferredFrameBuffer = new Framebuffer();
    m_gAlbedo = new Texture();
    m_gAlbedo->SetData(600, 600, Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE, nullptr);
    m_gNormal = new Texture();
    m_gNormal->SetData(600, 600, Texture::InternalFormat::RGB32F, Texture::Format::RGB, Texture::Type::FLOAT, nullptr);
    m_depthStencil = new Renderbuffer();
    m_depthStencil->SetData(600, 600, Renderbuffer::InternalFormat::DEPTH24_STENCIL8);
    m_deferredFrameBuffer->AttachDepthStencil(m_depthStencil);
    m_deferredFrameBuffer->AttachTexture(0, m_gAlbedo);
    m_deferredFrameBuffer->AttachTexture(1, m_gNormal);
    m_deferredFrameBuffer->SetDrawBuffer(0);
    m_deferredFrameBuffer->SetDrawBuffer(1);
}

void RenderManager::TearDown()
{
    delete m_renderWindow;
}
} // namespace spy
