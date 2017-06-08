#include "SceneObject.hpp"

uint64_t SceneObject::mCounter{};

SceneObject::SceneObject()
        : mId(mCounter),
          mReelNumber(0),
          mPosition(0, 0),
          mSize(1, 1),
          mVelocity(0.0f),
          mColor(1.0f),
          mRotation(0.0f) {
    ++mCounter;
}

SceneObject::SceneObject(uint32_t reelNumber,
                         glm::vec2 const & pos,
                         glm::vec2 const & size,
                         glm::vec3 const & color,
                         glm::vec2 const & velocity,
                         std::shared_ptr<Texture> texture)
        : mId{mCounter},
          mReelNumber{reelNumber},
          mPosition{pos},
          mSize{size},
          mVelocity{velocity},
          mColor{color},
          mRotation{0.0f},
          mPtrTexture{texture}{
    ++mCounter;
}


void SceneObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(mPtrTexture,
                        mPosition,
                        mSize,
                        mRotation,
                        mColor);

}

//Getters
void SceneObject::SetReelNumber(uint32_t reelNumber) noexcept {
    mReelNumber = reelNumber;
}

void SceneObject::SetPosition(const glm::vec2 &position) noexcept {
    mPosition = position;
}

void SceneObject::SetSize(const glm::vec2 &size) noexcept {
    mSize = size;
}

void SceneObject::SetVelocity(const glm::vec2 &velocity) noexcept {
    mVelocity = velocity;
}

void SceneObject::SetColor(const glm::vec3 &color) noexcept {
    mColor = color;
}

void SceneObject::SetRotation(GLfloat rotation) noexcept {
    mRotation = rotation;
}

void SceneObject::SetReadyForStart(bool isReady) noexcept {
    mReadyForStart = isReady;
}



// Setters
uint32_t SceneObject::GetReelNumber() const noexcept {
    return mReelNumber;
}

uint32_t SceneObject::GetId() const noexcept {
    return mId;
}

const glm::vec2 &SceneObject::GetPosition() const noexcept {
    return mPosition;
}

const glm::vec2 &SceneObject::GetSize() const noexcept {
    return mSize;
}

const glm::vec2 &SceneObject::GetVelocity() const noexcept {
    return mVelocity;
}

const glm::vec3 &SceneObject::GetColor() const noexcept {
    return mColor;
}

GLfloat SceneObject::GetRotation() const noexcept {
    return mRotation;
}

bool SceneObject::GetReadyForStart() const noexcept {
    return mReadyForStart;
}





