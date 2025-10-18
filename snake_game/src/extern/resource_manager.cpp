#include "resource_manager.h"
#include "shader.h"
#include "stb_image.h"
#include "texture.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture2D> ResourceManager::textures;


Shader ResourceManager::load_shader(const char *v_shader_file, const char *f_shader_file, std::string name)
{
    shaders[name] = load_shader_from_file(v_shader_file, f_shader_file);
    return shaders[name];
}

Shader ResourceManager::get_shader(std::string name)
{
    return shaders[name];
}

Texture2D ResourceManager::load_texture(const char *file, bool alpha, std::string name)
{
    textures[name] = load_texture_from_file(file, alpha);
    return textures[name];
}

Texture2D &ResourceManager::get_texture(std::string name)
{
    return textures.at(name);
}

void ResourceManager::clear()
{
    for (auto it : shaders)
        glDeleteProgram(it.second.ID);
    for (auto it: textures)
        glDeleteTextures(1, &it.second.ID);
}

Shader ResourceManager::load_shader_from_file(const char *v_shader_file, const char *f_shader_file)
{
    std::string vertex_code;
    std::string fragment_code;

    try {
        std::ifstream vertex_shader_file(v_shader_file);
        std::ifstream fragment_shader_file(f_shader_file);
        std::stringstream v_shader_stream, f_shader_stream;

        // read file buffer into streams
        v_shader_stream << vertex_shader_file.rdbuf();
        f_shader_stream << fragment_shader_file.rdbuf();

        // close when done reading
        vertex_shader_file.close();
        fragment_shader_file.close();

        // convert stream to string
        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str();
    }
    catch (std::exception e) {
        std::cout << "ERROR::SHADER: Failed to read shader files\n";
    }
    const char *v_shader_code = vertex_code.c_str();
    const char *f_shader_code = fragment_code.c_str();

    Shader shader;
    shader.compile(v_shader_code, f_shader_code);
    return shader;
}

Texture2D ResourceManager::load_texture_from_file(const char *file, bool alpha)
{
    Texture2D texture;
    if (alpha) {
        texture.internal_format = GL_RGBA;
        texture.image_format = GL_RGBA;
    }
    // load image
    int width, height, nr_channels;
    unsigned char *data = stbi_load(file, &width, &height, &nr_channels, 0);

    texture.generate(width, height, data);
    // free image data
    stbi_image_free(data);
    return texture;
}
