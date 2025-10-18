#pragma once

#include <map>
#include "shader.h"
#include "texture.h"

class ResourceManager {
public:
    // resoure storage
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2D> textures;

    // loads and generates a shader program from vertex and fragment file
    static Shader load_shader(const char *v_shader_file, const char *f_shader_file, std::string name);
    // get a stored shader 
    static Shader get_shader(std::string name);

    // loads and generates texture files
    static Texture2D load_texture(const char *file, bool alpha, std::string name);
    // get a stored texture
    static Texture2D &get_texture(std::string name);

    // cleanup function
    static void clear();
private:
    // private constructor
    ResourceManager() {}

    static Shader load_shader_from_file(const char *v_shader_file, const char *f_shader_file);
    static Texture2D load_texture_from_file(const char *file, bool alpha);
};


