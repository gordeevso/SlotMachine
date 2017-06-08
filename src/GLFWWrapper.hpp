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

    void GetCursorPos(double * posX, double * posY);
    static bool GetMouseButtonState();

    GLFWwindow* const GetWindow() const noexcept;
    GLuint      const GetWidth() const noexcept;
    GLuint      const GetHeight() const noexcept;

private:
    static void MouseButtonStateCallback(GLFWwindow *window,
                                         int32_t button,
                                         int32_t action,
                                         int32_t mods);
private:
    GLuint mWidth;
    GLuint mHeight;
    GLFWwindow* mpWindow;

    static bool mMouseButtonPressed;
};