
#include "GLFWWrapper.hpp"


GLFWWrapper::GLFWWrapper() : mWidth{800},
                         mHeight{384}
{}

GLFWWrapper::~GLFWWrapper() {
    glfwTerminate();
}

void GLFWWrapper::Init()  {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    mpWindow = glfwCreateWindow(mWidth, mHeight, "SlotMachine", nullptr, nullptr);
    glfwMakeContextCurrent(mpWindow);
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    glViewport(0, 0, mWidth, mHeight);
}

bool GLFWWrapper::CheckCloseWindow() const {
    return static_cast<bool>(glfwWindowShouldClose(mpWindow));
}

void GLFWWrapper::PollEvents() const {
    glfwPollEvents();
}

void GLFWWrapper::SwapBuffers() {
    glfwSwapBuffers(mpWindow);
}

GLFWwindow * const GLFWWrapper::GetWindow() const noexcept {
    return mpWindow;
}

GLuint const GLFWWrapper::GetWidth() const noexcept {
    return mWidth;
}

GLuint const GLFWWrapper::GetHeight() const noexcept {
    return mHeight;
}





