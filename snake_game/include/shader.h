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
    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;

    void set_vec2(const std::string &name, glm::vec2 &value) const;
    void set_vec2(const std::string &name, float x, float y) const;

    void set_mat2(const std::string &name, glm::mat2 &mat) const;
    void set_mat3(const std::string &name, glm::mat3 &mat) const;
    void set_mat4(const std::string &name, glm::mat4 &mat) const;
private:
    void check_compile_errors(unsigned int shader, std::string type);
};
