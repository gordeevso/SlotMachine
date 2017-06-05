#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLContext
{
public:
    static GLContext * GetInstance() {
        static GLContext instance;
        return &instance;
    }

private:
    GLContext();
    GLContext(GLContext const &) = delete;
    GLContext & operator=(GLContext const &) = delete;

public:
    ~GLContext();

    void Init();

    bool CheckCloseWindow() const;
    void PollEvents() const;
    void SwapBuffers();

    GLFWwindow* const GetWindow() const noexcept;
    GLuint      const GetWidth() const noexcept;
    GLuint      const GetHeight() const noexcept;

private:
    GLuint mWidth;
    GLuint mHeight;
    GLFWwindow* mpWindow;

};