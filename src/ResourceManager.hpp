#pragma once

#include <unordered_map>
#include <string>

#include "Shader.hpp"
#include "Texture.hpp"

typedef std::unordered_map<std::string, Shader> ShaderUMap;
typedef std::unordered_map<std::string, Texture> TextureUMap;

class ResourceManager {
public:
    static void LoadShader(std::string const &vs_file_path,
                             std::string const &fs_file_path,
                             std::string const &program_name);
    static void LoadTexture(std::string const &texture_path,
                               GLboolean alpha,
                               std::string const &name);

    static Shader & GetShader(std::string const &name);
    static Texture & GetTexture(std::string const &name);

private:
    ResourceManager() = delete;
    ResourceManager(ResourceManager const &) = delete;
    ResourceManager &operator=(ResourceManager const &) = delete;

    static Shader LoadShaderFromFile(std::string const &vs_file_path,
                                     std::string const &fs_file_path);

    static Texture loadTextureFromFile(std::string const &texture_path,
                                       GLboolean alpha);

private:
    static ShaderUMap mShaders;
    static TextureUMap mTextures;
};




