#pragma once
#include <glad/glad.h>

class Texture2D {
public:

    // default constructor
    Texture2D();

    // ID of texture objects
    GLuint ID;

    // image dimensions
    GLuint width, height;

    // texture format
    GLuint internal_format;
    GLuint image_format;

    // texture configuration
    GLuint wrap_s;      // wrapping mode on S axis
    GLuint wrap_t;      // wrapping mode on T axis             
    GLuint filter_min;  // filtering mode if px < screen px
    GLuint filter_max;  // filtering mode if px > screen px

    // generate texture from image data
    void generate(GLuint width, GLuint height, unsigned char *data);
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void bind() const;

};
