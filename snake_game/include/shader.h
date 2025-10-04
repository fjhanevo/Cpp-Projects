#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    // program ID
    unsigned int ID;

    // Constructor
    Shader() { }
 
    // sets current shader as active
    Shader &use();

    // compile shader from given code
    void compile(const char *vertex_source, const char *fragment_source);
    // some utility unifrom functions
    void set_int(const std::string &name, int value, bool use_shader = false);
    void set_float(const std::string &name, float value, bool use_shader = false);

    void set_vec2(const std::string &name, glm::vec2 &value, bool use_shader = false);
    void set_vec2(const std::string &name, float x, float y, bool use_shader = false);

    void set_vec3(const std::string &name, glm::vec3 &value, bool use_shader = false);
    void set_vec3(const std::string &name, float x, float y,float z, bool use_shader = false);

    void set_vec4(const std::string &name, glm::vec4 &value, bool use_shader = false);
    void set_vec4(const std::string &name, float x, float y,float z, float w, bool use_shader = false);

    void set_mat2(const std::string &name, glm::mat2 &mat, bool use_shader = false);
    void set_mat3(const std::string &name, glm::mat3 &mat, bool use_shader = false);
    void set_mat4(const std::string &name, glm::mat4 &mat, bool use_shader = false);
private:
    void check_compile_errors(unsigned int shader, std::string type);
};
