#include "RenderManager.hpp"
#include "Components/Rendering/CameraComponent.hpp"
#include "Components/Rendering/DirectionalLightComponent.hpp"
#include "Components/Rendering/JointComponent.hpp"
#include "Components/Rendering/MeshComponent.hpp"
#include "Components/Rendering/PointLightComponent.hpp"
#include "Components/Rendering/SkinnedMeshComponent.hpp"
#include "Components/Rendering/SpotlightComponent.hpp"
#include "FileSystem.hpp"
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

Transform* RenderManager::PickMesh(const glm::vec3& direction, const glm::vec3& origin)
{
    std::vector<MeshComponent*> hits;
    for (auto meshComponent : m_meshComponents)
    {
        glm::vec3 center = meshComponent->GetTransform()->GetWorldPosition();
        glm::vec3 l = center - origin;
        f32 s = glm::dot(l, direction);
        f32 l2 = glm::dot(l, l);
        f32 r = meshComponent->GetSphereRadius();
        f32 r2 = r * r;

        // Miss.
        if (s < 0 && l2 > r2)
        {
            continue;
        }

        f32 s2 = s * s;
        f32 m2 = l2 - s2;

        // Miss.
        if (m2 > r2)
        {
            continue;
        }

        // std::cout << "HIT!\n";
        // hits.push_back(meshComponent);
        return meshComponent->GetTransform();
    }

    return nullptr;
}

void RenderManager::RenderSceneToTexture(const glm::mat4& viewProjection)
{
    m_meshShader->Use();
    int32 lightCount = 0;
    for (auto directionalLight : m_directionalLightComponents)
    {
        glm::mat4 model = directionalLight->GetTransform()->GetWorldMatrix();
        m_meshShader->SetVec3Slow("directionalLights[" + std::to_string(lightCount) + "].direction", glm::normalize(glm::vec3(-model[0])));
        m_meshShader->SetVec3Slow("directionalLights[" + std::to_string(lightCount) + "].color", glm::vec3(1.0f, 1.0f, 1.0f));
        m_meshShader->SetFloatSlow("directionalLights[" + std::to_string(lightCount) + "].intensity", 1.0f);
        ++lightCount;
    }
    m_meshShader->SetIntSlow("directionalLightCount", lightCount);

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

void RenderManager::SetUp()
{
    m_renderWindow = new RenderWindow("Spy Editor", 1280, 720);

    m_meshShader = new Shader();
    m_meshShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/DefaultMesh.vs.glsl"), Shader::Type::VERTEX_SHADER);
    m_meshShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/DefaultMesh.fs.glsl"), Shader::Type::FRAGMENT_SHADER);
    m_meshShader->LinkProgram();
}

void RenderManager::TearDown()
{
    delete m_renderWindow;
}
} // namespace spy
