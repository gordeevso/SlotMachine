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

    void SetReelNumber(uint32_t reelNumber) noexcept;
    void SetPosition(glm::vec2 const &position) noexcept;
    void SetSize(glm::vec2 const &size) noexcept;
    void SetVelocity(glm::vec2 const &velocity) noexcept;
    void SetColor(glm::vec3 const &color) noexcept;
    void SetRotation(GLfloat rotation) noexcept;
    void SetReadyForStart(bool isReady) noexcept;

    uint32_t GetId() const noexcept;
    uint32_t GetReelNumber() const noexcept;
    glm::vec2 const & GetPosition() const noexcept;
    glm::vec2 const & GetSize() const noexcept;
    glm::vec2 const & GetVelocity() const noexcept;
    glm::vec3 const & GetColor() const noexcept;
    GLfloat           GetRotation() const noexcept;
    bool              GetReadyForStart() const noexcept;

private:
    uint64_t    mId;
    uint32_t    mReelNumber;
    glm::vec2   mPosition;
    glm::vec2   mSize;
    glm::vec2   mVelocity;
    glm::vec3   mColor;
    GLfloat     mRotation;
    std::shared_ptr<Texture> mPtrTexture;
    bool        mReadyForStart = false;
    static uint64_t mCounter;
};

