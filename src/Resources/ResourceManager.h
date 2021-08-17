#pragma once

/*
           ╔══════════════════════════════════╗
           ║	   CREATED BY L1derSobak      ║
           ║   Date of creating: Aug 14, 2021 ║
           ╚══════════════════════════════════╝
*/


#include <string>
#include <memory>
#include <map>

namespace Renderer
{
    class ShaderProgram;
    class Texture2D;
}


class ResourceManager {
public:
    ResourceManager(const std::string& executablePath);
    
    std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
    std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);

    std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
    std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);

    ~ResourceManager() = default;
private:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    std::string getFileString(const std::string& relativeFilePath) const;

    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> shaderProgramsMap;
    shaderProgramsMap shaderPrograms;

    typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> texturesMap;
    texturesMap textures;

    std::string path;
};