#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLFWWrapper
{
public:
    static GLFWWrapper * GetInstance() {
        static GLFWWrapper instance;
        return &instance;
    }

private:
    GLFWWrapper();
    GLFWWrapper(GLFWWrapper const &) = delete;
    GLFWWrapper & operator=(GLFWWrapper const &) = delete;

public:
    ~GLFWWrapper();

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