#pragma once

#include <GL/glew.h>

class Texture
{
public:
    Texture();
    ~Texture();

    Texture(Texture const &) = default;
    Texture & operator=(Texture const &) = default;

    void setInternalFormat(GLuint internalFormat) noexcept ;
    void setImageFormat(GLuint imageFormat) noexcept ;

    GLuint const GetInternalFormat() const noexcept ;
    GLuint const GetImageFormat() const noexcept ;

    void Generate(GLint width,
                  GLint height,
                  uint8_t * data);
    void Bind() const noexcept ;

private:
    GLuint mId;
    GLuint mInternalFormat;
    GLuint mImageFormat;
    GLuint mWrapS;
    GLuint mWrapT;
    GLuint mFilterMin;
    GLuint mFilterMax;
    GLfloat mAspectRatio;
};


