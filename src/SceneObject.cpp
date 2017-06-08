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
                         glm::vec2 const & velocity)
        : mId(mCounter),
          mReelNumber(reelNumber),
          mPosition(pos),
          mSize(size),
          mVelocity(velocity),
          mColor(color),
          mRotation(0.0f) {
    ++mCounter;
}


void SceneObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawRectangle(mPosition,
                           mSize,
                           mRotation,
                           mColor);

}

void SceneObject::SetReelNumber(uint32_t reelNumber) {
    mReelNumber = reelNumber;
}

void SceneObject::SetPosition(const glm::vec2 &position) {
    mPosition = position;
}

void SceneObject::SetSize(const glm::vec2 &size) {
    mSize = size;
}

void SceneObject::SetVelocity(const glm::vec2 &velocity) {
    mVelocity = velocity;
}

void SceneObject::SetColor(const glm::vec3 &color) {
    mColor = color;
}

void SceneObject::SetRotation(GLfloat rotation) {
    mRotation = rotation;
}



uint32_t SceneObject::GetReelNumber() const {
    return mReelNumber;
}

uint32_t SceneObject::GetId() const {
    return mId;
}

const glm::vec2 &SceneObject::GetPosition() const {
    return mPosition;
}

const glm::vec2 &SceneObject::GetSize() const {
    return mSize;
}

const glm::vec2 &SceneObject::GetVelocity() const {
    return mVelocity;
}

const glm::vec3 &SceneObject::GetColor() const {
    return mColor;
}

GLfloat SceneObject::GetRotation() const {
    return mRotation;
}





