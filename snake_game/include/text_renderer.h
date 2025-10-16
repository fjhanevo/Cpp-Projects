#pragma once 

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>

#include "texture.h"
#include "shader.h"

// holds state information relevant to a character as loaded using Freetype
struct Character {
    unsigned int TextureID;     // ID handle of the glyph texture
    glm::ivec2   size;          // size of glyph
    glm::ivec2   bearing;       // offset from baseline to left/top of glyph
    long advance;       // horizontal offset to advance to the next glyph
};

class TextRenderer
{
public:
    // holds pre-compiled characters
    std::map<char, Character> characters;
    Shader text_shader; 
    TextRenderer(unsigned int width, unsigned int height);
    // precomples a list of characters from the 
    void load(std::string font, unsigned int font_size);
    // renders a string of text using the precompiled list of characters
    void render_text(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
private:
    unsigned int VAO, VBO;
};
