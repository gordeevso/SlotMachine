#include <iostream>
#include "GLContext.hpp"
#include "SpriteRenderer.hpp"
#include "ResourceManager.hpp"

std::string const SPRITE_SHADER = "sprite_shader";
std::string const RECTANGLE_SHADER = "rectangle";

SpriteRenderer::SpriteRenderer(RenderType const render_type) : mShader{},
                                                               mVAO{},
                                                               mVBO{} {
    switch(render_type) {
        case SPRITE: InitSpriteRenderData();
        case RECTANGLE: InitRectangleRenderData();
    }
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
}

void SpriteRenderer::InitSpriteRenderData()
{
    ResourceManager::LoadShader("../shaders/sprite.vs", "../shaders/sprite.fs", SPRITE_SHADER);

//    ResourceManager::LoadTexture("textures/sky.png", GL_TRUE, "sky");
//    ResourceManager::LoadTexture("textures/sky.png", GL_TRUE, "rect");

    glm::mat4 projection = glm::ortho(0.0f,
                                      static_cast<GLfloat>(GLContext::GetInstance()->GetWidth()),
                                      static_cast<GLfloat>(GLContext::GetInstance()->GetHeight()),
                                      0.0f,
                                      -1.0f,
                                      1.0f);

    ResourceManager::GetShader(SPRITE_SHADER).Use();
    ResourceManager::GetShader(SPRITE_SHADER).SetInteger("sprite", 0);
    ResourceManager::GetShader(SPRITE_SHADER).SetMatrix4("projection", projection);

    mShader = ResourceManager::GetShader(SPRITE_SHADER);

    GLfloat vertices[] =
            {
                    0.0f, 0.0f,     0.0f, 0.0f,
                    1.0f, 0.0f,     1.0f, 0.0f,
                    0.0f, 1.0f,     0.0f, 1.0f,
                    1.0f, 1.0f,     1.0f, 1.0f
            };

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindVertexArray(mVAO);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(Texture const & texture,
                                glm::vec2 const & position,
                                glm::vec2 const & size,
                                GLfloat rotate_degrees,
                                glm::vec3 const & color)
{
    // Prepare transformations
    mShader.Use();
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate_degrees), glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate_degrees
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

    mShader.SetMatrix4("model", model);
    mShader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void SpriteRenderer::InitRectangleRenderData()
{
    ResourceManager::LoadShader("../shaders/rectangle.vs", "../shaders/rectangle.fs", RECTANGLE_SHADER);
    mShader = ResourceManager::GetShader(RECTANGLE_SHADER);

    glm::mat4 projection = glm::ortho(0.0f,
                                      static_cast<GLfloat>(GLContext::GetInstance()->GetWidth()),
                                      static_cast<GLfloat>(GLContext::GetInstance()->GetHeight()),
                                      0.0f,
                                      -1.0f,
                                      1.0f);


    mShader.Use();
    mShader.SetMatrix4("projection", projection);

    GLfloat vertices[] =
            {
                    0.0f, 0.0f,
                    1.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f
            };

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindVertexArray(mVAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawRectangle(glm::vec2 const & position,
                                   glm::vec2 const & size,
                                   GLfloat rotate_degrees,
                                   glm::vec3 const & color)
{
    // Prepare transformations
    mShader.Use();
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate_degrees), glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate_degrees
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

    mShader.SetMatrix4("model", model);
    mShader.SetVector3f("un_rectangle_color", color);

    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}