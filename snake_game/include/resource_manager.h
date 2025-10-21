#pragma once

#include <map>
#include <filesystem>
#include "shader.h"
#include "texture.h"

namespace fs = std::filesystem;
class ResourceManager {
public:
    // resoure storage
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2D> textures;

    // loads and generates a shader program from vertex and fragment file
    static Shader load_shader(const fs::path &v_shader_file, const fs::path &f_shader_file, std::string name);
    // get a stored shader 
    static Shader get_shader(std::string name);

    // loads and generates texture files
    static Texture2D load_texture(const std::filesystem::path &file, bool alpha, std::string name);
    // get a stored texture
    static Texture2D &get_texture(std::string name);

    // cleanup function
    static void clear();
private:
    // private constructor
    ResourceManager() {}

    static Shader load_shader_from_file(const fs::path &v_shader_file, const fs::path &f_shader_file);
    static Texture2D load_texture_from_file(const fs::path &file, bool alpha);
};


