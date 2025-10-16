#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "text_renderer.h"
#include "config.h"
#include "resource_manager.h"
#include <ft2build.h>
#include FT_FREETYPE_H

std::string text_vert_path = std::string(RESOURCE_DIR) + "/shaders/text.vert";
std::string text_frag_path = std::string(RESOURCE_DIR) + "/shaders/text.frag";

TextRenderer::TextRenderer(unsigned int width, unsigned int height)
{
    // load and configure shaders
    this->text_shader = ResourceManager::load_shader(text_vert_path.c_str(), text_frag_path.c_str(), "text");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);
    this->text_shader.set_mat4("projection", projection, true);
    this->text_shader.set_int("text", 0);
    // configure VAO/VBO for texture quads
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::load(std::string font, unsigned int font_size)
{
    // clear the previously loaded characters
    this->characters.clear();
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library\n";
    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font\n";
    
    // set the size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, font_size);
    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // for the first 128 ASCII character, pre-load/compile and store them
    for (GLubyte c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph\n";
            continue;
        }

        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters.insert(std::pair<char, Character>(c, character));

    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // destroy when finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::render_text(std::string text, float x, float y, float scale, glm::vec3 color)
{
    this->text_shader.use();
    this->text_shader.set_vec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = characters[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y + (this->characters['H'].bearing.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        // update VBO for each character
        float vertices[6][4] = {
            { xpos,         ypos + h,       0.0f, 1.0f },
            { xpos + w,     ypos,           1.0f, 0.0f },
            { xpos,         ypos,           0.0f, 0.0f },

            { xpos,         ypos + h,       0.0f, 1.0f },
            { xpos + w,     ypos + h,       1.0f, 1.0f },
            { xpos + w,     ypos,           1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferSubData(GL_ARRAY_BUFFER , 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph
        x += (ch.advance >> 6) * scale;     // bitshift by 6
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


