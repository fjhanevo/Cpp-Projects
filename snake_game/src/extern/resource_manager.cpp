#include "resource_manager.h"

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture2D> ResourceManager::textures;

Shader ResourceManager::load_shader(const char *v_shader_file, const char *f_shader_file, std::string name)
{
    shaders[name] = load_shader_from_file(v_shader_file, f_shader_file);
    return shaders[name];
}

Texture2D ResourceManager::load_texture(const char *file, bool alpha, std::string name)
{
    textures[name] = load_texture_from_file(file, alpha);
    return textures[name];
}
