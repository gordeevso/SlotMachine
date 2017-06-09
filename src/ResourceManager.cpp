#include <fstream>
#include <sstream>
#include <iostream>
#include <SOIL.h>

#include "ResourceManager.hpp"

TextureMap ResourceManager::mTextures;
ShaderMap ResourceManager::mShaders;
std::vector<std::string> ResourceManager::mTextureNames;

//Shader-specific functions
Shader & ResourceManager::GetShader(std::string const &name) {
    return mShaders[name];
}

void ResourceManager::LoadShader(std::string const &vs_file_path,
                                   std::string const &fs_file_path,
                                   std::string const &program_name) {
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

    mShaders.insert(std::move(std::make_pair(program_name, Shader{})));
    mShaders[program_name].CreateProgram(vs_source, fs_source);
}



//Texture-specific functions
std::shared_ptr<Texture> ResourceManager::GetTexture(std::string const &name) {
    return mTextures[name];
}

void ResourceManager::LoadTexture(std::string const &texture_file,
                                  GLboolean alpha,
                                  std::string const &name) {
    mTextures.insert(std::move(std::make_pair(name, new Texture{})));
    mTextureNames.push_back(name);

    if (alpha) {
        mTextures[name]->SetImageFormat(GL_RGBA);
        mTextures[name]->SetInternalFormat(GL_RGBA);
    }

    int32_t width{};
    int32_t height{};
    uint8_t *image = SOIL_load_image(texture_file.c_str(),
                                     &width,
                                     &height,
                                     0,
                                     mTextures[name]->GetImageFormat() == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

    mTextures[name]->Generate(width, height, image);

    SOIL_free_image_data(image);

//    std::cout << "w = " << width
//              << " h = " << height
//              << " id = " << mTextures[name]->GetId()
//              << " alpha = " << (int)alpha << " "
//              << name
//              << "\n";

}

std::vector<std::string> const & ResourceManager::GetTextureNames() {
    return mTextureNames;
}





