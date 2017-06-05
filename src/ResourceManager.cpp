#include <fstream>
#include <sstream>
#include <iostream>
#include <SOIL.h>

#include "ResourceManager.hpp"

TextureUMap ResourceManager::mTextures;
ShaderUMap ResourceManager::mShaders;

//Shader-specific functions
Shader & ResourceManager::GetShader(std::string const &name) {
    return mShaders[name];
}

void ResourceManager::LoadShader(std::string const &vs_file_path,
                                   std::string const &fs_file_path,
                                   std::string const &program_name) {
    mShaders.insert(std::move(std::make_pair(program_name, LoadShaderFromFile(vs_file_path, fs_file_path))));
}

Shader ResourceManager::LoadShaderFromFile(std::string const &vs_file_path,
                                           std::string const &fs_file_path) {
    std::string vs_source;
    std::string fs_source;

    std::ifstream handle_vs_file(vs_file_path);
    if(handle_vs_file.is_open()) {
        std::stringstream ss_vs;
        ss_vs << handle_vs_file.rdbuf();
        vs_source = ss_vs.str();
    }
    else {
        throw std::invalid_argument(vs_file_path);
    }

    std::ifstream handle_fs_file(fs_file_path);
    if(handle_fs_file.is_open()) {
        std::stringstream ss_fs;
        ss_fs << handle_fs_file.rdbuf();
        fs_source = ss_fs.str();
    }
    else {
        throw std::invalid_argument(fs_file_path);
    }

    Shader shader;
    shader.CreateProgram(vs_source, fs_source);

    return shader;
}


//Texture-specific functions
Texture & ResourceManager::GetTexture(std::string const &name) {
    return mTextures[name];
}

void ResourceManager::LoadTexture(std::string const &texture_file,
                                  GLboolean alpha,
                                  std::string const &name) {
    mTextures.insert(std::move(std::make_pair(name, loadTextureFromFile(texture_file, alpha))));
}

Texture ResourceManager::loadTextureFromFile(std::string const &texture_file,
                                             GLboolean alpha) {
    Texture texture{};

    if (alpha) {
        texture.setImageFormat(GL_RGBA);
        texture.setInternalFormat(GL_RGBA);
    }

    int32_t width{};
    int32_t height{};
    uint8_t *image = SOIL_load_image(texture_file.c_str(),
                                     &width,
                                     &height,
                                     0,
                                     texture.GetImageFormat() == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

    texture.Generate(width, height, image);

    SOIL_free_image_data(image);
    return texture;
}



