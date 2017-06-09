#pragma once

#include <GL/glew.h>

#include "Shader.hpp"

class RenderToTexture {
public:
    RenderToTexture();
    ~RenderToTexture();
    RenderToTexture(RenderToTexture const &) = default;
    RenderToTexture &operator=(RenderToTexture const &) = default;

    void Init();
    void PreRender();
    void PostRender();

private:
    Shader mShader;
    GLuint mFBO;
    GLuint mTBO;
    GLuint mRBO;
    GLuint mVAO;
    GLuint mVBO;
};
