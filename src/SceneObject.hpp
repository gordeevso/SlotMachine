#pragma once

#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.hpp"
#include "SpriteRenderer.hpp"

class SceneObject
{
public:
    SceneObject();
    SceneObject(uint32_t reelNumber,
                glm::vec2 const & pos,
                glm::vec2 const & size,
                glm::vec3 const & color,
                glm::vec2 const & velocity,
                std::shared_ptr<Texture> texture);

    ~SceneObject() = default;
    void Draw(SpriteRenderer &renderer);

    void SetReelNumber(uint32_t reelNumber);
    void SetPosition(glm::vec2 const &position);
    void SetSize(glm::vec2 const &size);
    void SetVelocity(glm::vec2 const &velocity);
    void SetColor(glm::vec3 const &color);
    void SetRotation(GLfloat rotation);

    uint32_t GetId() const;
    uint32_t GetReelNumber() const;
    glm::vec2 const & GetPosition() const;
    glm::vec2 const & GetSize() const;
    glm::vec2 const & GetVelocity() const;
    glm::vec3 const & GetColor() const;
    GLfloat           GetRotation() const;

private:
    uint64_t    mId;
    uint32_t    mReelNumber;
    glm::vec2   mPosition;
    glm::vec2   mSize;
    glm::vec2   mVelocity;
    glm::vec3   mColor;
    GLfloat     mRotation;
    std::shared_ptr<Texture> mPtrTexture;
    static uint64_t mCounter;
};

