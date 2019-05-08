#include "RenderManager.hpp"
#include "Components/Rendering/CameraComponent.hpp"
#include "Components/Rendering/DirectionalLightComponent.hpp"
#include "Components/Rendering/JointComponent.hpp"
#include "Components/Rendering/MeshComponent.hpp"
#include "Components/Rendering/PointLightComponent.hpp"
#include "Components/Rendering/SkinnedMeshComponent.hpp"
#include "Components/Rendering/SpotlightComponent.hpp"
#include "Components/Rendering/TerrainComponent.hpp"
#include "FileSystem.hpp"
#include "SketchInclude.hpp"
#include "UtilsInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "Rendering/Terrain.hpp"
#include "Transform.hpp"

namespace snack
{
RenderManager::RenderManager()
    : m_renderWindow(nullptr)
    , m_meshShader(nullptr)
    , m_skinnedMeshShader(nullptr)
    , m_deferredFrameBuffer(nullptr)
    , m_gAlbedo(nullptr)
    , m_gNormal(nullptr)
    , m_depthStencil(nullptr)
  
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

void RenderManager::RenderSceneToTexture(Framebuffer* framebuffer, int32 width, int32 height)
{
    if (width != m_gPosition->GetWidth() || height != m_gPosition->GetHeight())
    {
        m_gPosition->SetData(width, height, Texture::InternalFormat::RGBA16F, Texture::Format::RGBA, Texture::Type::FLOAT, nullptr);
        m_gNormal->SetData(width, height, Texture::InternalFormat::RGBA16F, Texture::Format::RGBA, Texture::Type::FLOAT, nullptr);
        m_gAlbedo->SetData(width, height, Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE, nullptr);
        m_gMRA->SetData(width, height, Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE, nullptr);
        m_depthStencil->SetData(width, height, Renderbuffer::InternalFormat::DEPTH24_STENCIL8);
    }

    for (auto l : m_directionalLightComponents)
    {
        if (l->IsEnabled())
        {
            RenderToShadowMap(l);
            break;
        }
    }

    for (auto c : m_cameraComponents)
    {
        if (c->GetRenderMode() == CameraComponent::RenderMode::DEFERRED)
        {
            m_renderWindow->SetViewport(0, 0, m_gAlbedo->GetWidth(), m_gAlbedo->GetHeight());
            m_renderWindow->EnableCullFace(true);
            m_renderWindow->EnableDepthTest(true);
            DeferredGeometryPass(c);
            framebuffer->Bind();
            {
                DeferredLightingPass(c);
            }
            framebuffer->Unbind();
        }
        else 
        {
            framebuffer->Bind();
            {
                m_renderWindow->SetViewport(0, 0, width, height);
                m_renderWindow->EnableCullFace(true);
                m_renderWindow->EnableDepthTest(true);
                ForwardPass(c, width, height);
            }
            framebuffer->Unbind();
        }
    }
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
    m_meshShader->SetMat4Slow("ViewProjection", viewProjection);
    for (auto meshComponent : m_meshComponents)
    {
        Mesh* mesh = meshComponent->GetMesh();
        m_meshShader->SetMat4Slow("Model", meshComponent->GetTransform()->GetWorldMatrix());
        mesh->Render(Mesh::Mode::TRIANGLES);
    }

    m_terrainShader->Use();
    m_terrainShader->SetMat4Slow("ViewProjection", viewProjection);
    for (auto terrainComponent : m_terrainComponents)
    {
        Terrain* terrain = terrainComponent->GetTerrain();
        if (terrain)
        {
            m_terrainShader->SetMat4Slow("Model", terrainComponent->GetTransform()->GetWorldMatrix());
            terrain->Render();
        }
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

void RenderManager::DeregisterTerrainComponent(TerrainComponent* terrainComponent)
{
    m_terrainComponents.erase(terrainComponent);
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

void RenderManager::RegisterTerrainComponent(TerrainComponent* terrainComponent)
{
    m_terrainComponents.insert(terrainComponent);
}

void RenderManager::DeferredGeometryPass(CameraComponent* camera)
{
    m_deferredFrameBuffer->Bind();
    {
        m_renderWindow->SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        m_renderWindow->Clear();
        m_geometryPassShader->Use();
        m_geometryPassShader->SetMat4Slow("ViewProjection", camera->GetProjectionMatrix(m_gPosition->GetWidth(), m_gPosition->GetHeight()) * camera->GetViewMatrix());
        for (auto m : m_meshComponents)
        {
            Mesh* mesh = m->GetMesh();
            m_geometryPassShader->SetMat4Slow("Model", m->GetTransform()->GetWorldMatrix());
            Material* material = nullptr;
            if (material = m->GetMaterial())
            {
                Texture* albedo = nullptr;
                if (albedo = material->GetTexture("Albedo"))
                {
                    m_geometryPassShader->SetIntSlow("AlbedoMap", 0);
                    albedo->Bind(0);
                }
                Texture* normal = nullptr;
                if (normal = material->GetTexture("Normal"))
                {
                    m_geometryPassShader->SetIntSlow("NormalMap", 1);
                    normal->Bind(1);
                }
                Texture* metallic = nullptr;
                if (metallic = material->GetTexture("Metallic"))
                {
                    m_geometryPassShader->SetIntSlow("MetallicMap", 2);
                    metallic->Bind(2);
                }
                Texture* roughness = nullptr;
                if (roughness = material->GetTexture("Roughness"))
                {
                    m_geometryPassShader->SetIntSlow("RoughnessMap", 3);
                    roughness->Bind(3);
                }
                Texture* ao = nullptr;
                if (ao = material->GetTexture("AO"))
                {
                    m_geometryPassShader->SetIntSlow("AOMap", 4);
                    ao->Bind(4);
                }

                m_geometryPassShader->SetVec4Slow("AlbedoColor", material->GetColor("Albedo"));
                m_geometryPassShader->SetVec4Slow("NormalColor", material->GetColor("Normal"));
                m_geometryPassShader->SetVec4Slow("MetallicColor", material->GetColor("Metallic"));
                m_geometryPassShader->SetVec4Slow("RoughnessColor", material->GetColor("Roughness"));
                m_geometryPassShader->SetVec4Slow("AOColor", material->GetColor("AO"));
            }

            mesh->Render(Mesh::Mode::TRIANGLES);
        }
    }
    m_deferredFrameBuffer->Unbind();
}

void RenderManager::DeferredLightingPass(CameraComponent* camera)
{
    m_renderWindow->SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    m_renderWindow->Clear();

    m_lightingPassShader->Use();
    int32 lightCount = 0;
    for (auto directionalLight : m_directionalLightComponents)
    {
        glm::mat4 model = directionalLight->GetTransform()->GetWorldMatrix();
        m_lightingPassShader->SetVec3Slow("DirectionalLights[" + std::to_string(lightCount) + "].direction", glm::normalize(glm::vec3(-model[0])));
        m_lightingPassShader->SetVec3Slow("DirectionalLights[" + std::to_string(lightCount) + "].color", glm::vec3(1.0f, 1.0f, 1.0f));
        m_lightingPassShader->SetFloatSlow("DirectionalLights[" + std::to_string(lightCount) + "].intensity", directionalLight->GetIntensity());
        ++lightCount;
    }
    m_lightingPassShader->SetIntSlow("DirectionalLightCount", lightCount);
    lightCount = 0;
    for (auto pointLight : m_pointLightComponents)
    {
        glm::mat4 model = pointLight->GetTransform()->GetWorldMatrix();
        m_lightingPassShader->SetVec3Slow("PointLights[" + std::to_string(lightCount) + "].position", glm::vec3(model[3]));
        m_lightingPassShader->SetVec3Slow("PointLights[" + std::to_string(lightCount) + "].color", glm::vec3(1.0f, 1.0f, 1.0f));
        m_lightingPassShader->SetFloatSlow("PointLights[" + std::to_string(lightCount) + "].intensity", pointLight->GetIntensity());
        ++lightCount;
    }
    m_lightingPassShader->SetIntSlow("PointLightCount", lightCount);
    m_lightingPassShader->SetVec3Slow("ViewPosition", camera->GetTransform()->GetWorldPosition());
    m_lightingPassShader->SetIntSlow("GPosition", 0);
    m_lightingPassShader->SetIntSlow("GNormal", 1);
    m_lightingPassShader->SetIntSlow("GAlbedo", 2);
    m_lightingPassShader->SetIntSlow("GMRA", 3);
    m_gPosition->Bind(0);
    m_gNormal->Bind(1);
    m_gAlbedo->Bind(2);
    m_gMRA->Bind(3);
    m_fullScreenQuad->Render();
}

void RenderManager::ForwardPass(CameraComponent* camera, int32 width, int32 height)
{
    m_renderWindow->SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    m_renderWindow->Clear();

    m_pbrShader->Use();

    int32 lightCount = 0;
    for (auto directionalLight : m_directionalLightComponents)
    {
        glm::mat4 model = directionalLight->GetTransform()->GetWorldMatrix();
        m_pbrShader->SetVec3Slow("DirectionalLights[" + std::to_string(lightCount) + "].direction", glm::normalize(glm::vec3(-model[0])));
        m_pbrShader->SetVec3Slow("DirectionalLights[" + std::to_string(lightCount) + "].color", glm::vec3(1.0f, 1.0f, 1.0f));
        m_pbrShader->SetFloatSlow("DirectionalLights[" + std::to_string(lightCount) + "].intensity", directionalLight->GetIntensity());
        ++lightCount;
    }
    m_pbrShader->SetIntSlow("DirectionalLightCount", lightCount);
    lightCount = 0;
    for (auto pointLight : m_pointLightComponents)
    {
        glm::mat4 model = pointLight->GetTransform()->GetWorldMatrix();
        m_pbrShader->SetVec3Slow("PointLights[" + std::to_string(lightCount) + "].position", glm::vec3(model[3]));
        m_pbrShader->SetVec3Slow("PointLights[" + std::to_string(lightCount) + "].color", glm::vec3(1.0f, 1.0f, 1.0f));
        m_pbrShader->SetFloatSlow("PointLights[" + std::to_string(lightCount) + "].intensity", pointLight->GetIntensity());
        ++lightCount;
    }
    m_pbrShader->SetIntSlow("PointLightCount", lightCount);
    m_pbrShader->SetVec3Slow("ViewPosition", camera->GetTransform()->GetWorldPosition());

    m_pbrShader->SetMat4Slow("ViewProjection", camera->GetProjectionMatrix(width, height) * camera->GetViewMatrix());
    for (auto m : m_meshComponents)
    {
        Mesh* mesh = m->GetMesh();
        m_pbrShader->SetMat4Slow("Model", m->GetTransform()->GetWorldMatrix());
        Material* material = nullptr;
        if (material = m->GetMaterial())
        {
            Texture* albedo = nullptr;
            if (albedo = material->GetTexture("Albedo"))
            {
                m_pbrShader->SetIntSlow("AlbedoMap", 0);
                albedo->Bind(0);
            }
            Texture* normal = nullptr;
            if (normal = material->GetTexture("Normal"))
            {
                m_pbrShader->SetIntSlow("NormalMap", 1);
                normal->Bind(1);
            }
            Texture* metallic = nullptr;
            if (metallic = material->GetTexture("Metallic"))
            {
                m_pbrShader->SetIntSlow("MetallicMap", 2);
                metallic->Bind(2);
            }
            Texture* roughness = nullptr;
            if (roughness = material->GetTexture("Roughness"))
            {
                m_pbrShader->SetIntSlow("RoughnessMap", 3);
                roughness->Bind(3);
            }
            Texture* ao = nullptr;
            if (ao = material->GetTexture("AO"))
            {
                m_pbrShader->SetIntSlow("AOMap", 4);
                ao->Bind(4);
            }

            m_pbrShader->SetVec4Slow("AlbedoColor", material->GetColor("Albedo"));
            m_pbrShader->SetVec4Slow("NormalColor", material->GetColor("Normal"));
            m_pbrShader->SetVec4Slow("MetallicColor", material->GetColor("Metallic"));
            m_pbrShader->SetVec4Slow("RoughnessColor", material->GetColor("Roughness"));
            m_pbrShader->SetVec4Slow("AOColor", material->GetColor("AO"));
        }

        mesh->Render(Mesh::Mode::TRIANGLES);
    }
}

void RenderManager::RenderToShadowMap(DirectionalLightComponent* light)
{
    f32 nearPlane = 1.0f;
    f32 farPlane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);

    glm::mat4 lightView = glm::lookAt(light->GetTransform()->GetWorldPosition(),
        glm::vec3(0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    m_depthShader->Use();
    m_depthShader->SetMat4Slow("LightSpaceMatrix", lightSpaceMatrix);

    m_renderWindow->SetViewport(0, 0, m_shadowWidth, m_shadowHeight);
    m_renderWindow->ClearDepthBuffer();
    m_shadowMapFrameBuffer->Bind();

    for (auto meshComponent : m_meshComponents)
    {
        Mesh* mesh = meshComponent->GetMesh();
        m_depthShader->SetMat4Slow("Model", meshComponent->GetTransform()->GetWorldMatrix());
        //mesh->Render(Mesh::Mode::TRIANGLES);
    }

    m_shadowMapFrameBuffer->Unbind();
}

void RenderManager::SetUp()
{
    m_renderWindow = new RenderWindow("Snack Editor", 1280, 720);

    m_meshShader = new Shader();
    m_meshShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/DefaultMesh.vs.glsl"), Shader::Type::VERTEX_SHADER);
    m_meshShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/DefaultMesh.fs.glsl"), Shader::Type::FRAGMENT_SHADER);
    m_meshShader->LinkProgram();

    m_terrainShader = new Shader();
    m_terrainShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/Terrain.vs.glsl"), Shader::Type::VERTEX_SHADER);
    m_terrainShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/Terrain.tcs.glsl"), Shader::Type::TESSELATION_CONTROL_SHADER);
    m_terrainShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/Terrain.tes.glsl"), Shader::Type::TESSELATION_EVALUATION_SHADER);
    m_terrainShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/Terrain.gs.glsl"), Shader::Type::GEOMETRY_SHADER);
    m_terrainShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/Terrain.fs.glsl"), Shader::Type::FRAGMENT_SHADER);
    m_terrainShader->LinkProgram();

    m_pbrShader = new Shader();
    m_pbrShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/PBRMesh.vs.glsl"), Shader::Type::VERTEX_SHADER);
    m_pbrShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/PBRMesh.fs.glsl"), Shader::Type::FRAGMENT_SHADER);
    m_pbrShader->LinkProgram();

    // Deferred rendering.
    m_deferredFrameBuffer = new Framebuffer();

    m_gPosition = new Texture();
    m_gPosition->SetData(512, 512, Texture::InternalFormat::RGBA16F, Texture::Format::RGBA, Texture::Type::FLOAT, nullptr);
    m_gPosition->SetSWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_gPosition->SetTWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_deferredFrameBuffer->AttachTexture(0, m_gPosition);

    m_gNormal = new Texture();
    m_gNormal->SetData(512, 512, Texture::InternalFormat::RGBA16F, Texture::Format::RGBA, Texture::Type::FLOAT, nullptr);
    m_gNormal->SetSWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_gNormal->SetTWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_deferredFrameBuffer->AttachTexture(1, m_gNormal);

    m_gAlbedo = new Texture();
    m_gAlbedo->SetData(512, 512, Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE, nullptr);
    m_gAlbedo->SetSWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_gAlbedo->SetTWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_deferredFrameBuffer->AttachTexture(2, m_gAlbedo);

    m_gMRA = new Texture();
    m_gMRA->SetData(512, 512, Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE, nullptr);
    m_gMRA->SetSWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_gMRA->SetTWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_deferredFrameBuffer->AttachTexture(3, m_gMRA);

    // Set draw buffers.
    uint32 attachments[4] = { 0, 1, 2, 3 };
    m_deferredFrameBuffer->SetDrawBuffers(attachments, 4);

    // Depth and stencil.
    m_depthStencil = new Renderbuffer();
    m_depthStencil->SetData(512, 512, Renderbuffer::InternalFormat::DEPTH24_STENCIL8);
    m_deferredFrameBuffer->AttachDepthStencil(m_depthStencil);

    m_geometryPassShader = new Shader();
    m_geometryPassShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/GeometryPass.vs.glsl"), Shader::Type::VERTEX_SHADER);
    m_geometryPassShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/GeometryPass.fs.glsl"), Shader::Type::FRAGMENT_SHADER);
    m_geometryPassShader->LinkProgram();

    m_lightingPassShader = new Shader();
    m_lightingPassShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/LightingPass.vs.glsl"), Shader::Type::VERTEX_SHADER);
    m_lightingPassShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/LightingPass.fs.glsl"), Shader::Type::FRAGMENT_SHADER);
    m_lightingPassShader->LinkProgram();

    m_fullScreenQuad = new FullScreenQuad();

    // Shadow Maps
    m_shadowMapFrameBuffer = new Framebuffer();

    m_shadowMap = new Texture();
    m_shadowMap->SetData(m_shadowWidth, m_shadowHeight, Texture::InternalFormat::RGBA16F, Texture::Format::RGBA, Texture::Type::FLOAT, nullptr);
    m_shadowMap->SetSWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_shadowMap->SetTWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_shadowMapFrameBuffer->AttachDepthBuffer(m_shadowMap);

    m_depthShader = new Shader();
    m_depthShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/SimpleDepth.vs.glsl"), Shader::Type::VERTEX_SHADER);
    m_depthShader->LoadShaderFromFile(FileSystem::GetRelativeDataPath("Shaders/SimpleDepth.fs.glsl"), Shader::Type::FRAGMENT_SHADER);
    m_depthShader->LinkProgram();
}

void RenderManager::TearDown()
{
    delete m_renderWindow;
}
} // namespace snack
