#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.hpp"
#include "Texture.hpp"

enum RenderType
{
    SPRITE,
    RECTANGLE
};

class SpriteRenderer
{
public:
    SpriteRenderer() : mShader{},
                       mVAO{},
                       mVBO{}
    {}

    SpriteRenderer(RenderType const render_type);
    SpriteRenderer(SpriteRenderer const &) = delete;
    SpriteRenderer & operator=(SpriteRenderer const &) = delete;
    ~SpriteRenderer();

    void DrawSprite(Texture const & texture,
                    glm::vec2 const & position,
                    glm::vec2 const & size,
                    GLfloat rotate_degrees,
                    glm::vec3 const & color);

    void DrawRectangle(glm::vec2 const & position,
                       glm::vec2 const & size,
                       GLfloat rotate_degrees,
                       glm::vec3 const & color);

private:
    Shader mShader;
    GLuint mVAO;
    GLuint mVBO;

private:
    void InitSpriteRenderData();
    void InitRectangleRenderData();
};


