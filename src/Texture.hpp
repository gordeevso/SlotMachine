#pragma once

#include <GL/glew.h>

class Texture
{
public:
    Texture();
    ~Texture();

    Texture(Texture const &) = default;
    Texture & operator=(Texture const &) = default;

    void SetInternalFormat(GLuint internalFormat) noexcept ;
    void SetImageFormat(GLuint imageFormat) noexcept ;

    GLuint GetInternalFormat() const noexcept ;
    GLuint GetImageFormat() const noexcept ;

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


