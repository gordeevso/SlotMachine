#include <iostream>


#include "Shader.hpp"

Shader::Shader() : mId{0}
{}

Shader::~Shader() {
    DeleteProgram();
}

void Shader::DeleteProgram() {
    glDeleteProgram(mId);
}

GLuint const Shader::GetId() const {
    return mId;
}

void Shader::Use() const {
    glUseProgram(mId);
}

GLuint Shader::CreateShader(const GLenum shader_type,
                            const std::string &shader_source) const {
    GLint compile_result{};
    GLchar log[256];
    GLuint shader{};

    shader = glCreateShader(shader_type);
    const GLchar * pshader_code = shader_source.c_str();
    const GLint shader_code_size = shader_source.size();

    glShaderSource(shader, 1, &pshader_code, &shader_code_size);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

    if (compile_result == GL_FALSE) {
        glGetShaderInfoLog(shader, sizeof(log), 0, log);
        switch(shader_type) {
            case GL_VERTEX_SHADER:
                std::cerr << "Vertex shader_ error: " << log << std::endl;
                break;
            case GL_FRAGMENT_SHADER:
                std::cerr << "Fragment shader_ error: " << log << std::endl;
                break;
        }

        if (shader > 0) {
            glDeleteShader(shader);
        }
        return 0;
    }
    return shader;
}

void Shader::CreateProgram(const std::string& vertex_shader_code,
                           const std::string& fragment_shader_code) {
    GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code);
    GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code);

    GLchar log[256];
    GLint  link_result{};

    mId = glCreateProgram();
    glAttachShader(mId, vertex_shader);
    glAttachShader(mId, fragment_shader);

    glLinkProgram(mId);
    glGetProgramiv(mId, GL_LINK_STATUS, &link_result);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    if (link_result == GL_FALSE) {
        glGetProgramInfoLog(mId, sizeof(log), 0, log);
        std::cerr << "Shader program error: " << log << std::endl;
        return;
    }
}


void Shader::SetFloat(GLchar const *name, GLfloat value) {
    glUniform1f(glGetUniformLocation(mId, name), value);
}

void Shader::SetInteger(GLchar const *name, GLint value) {
    glUniform1i(glGetUniformLocation(mId, name), value);
}

void Shader::SetVector2f(GLchar const *name, GLfloat x, GLfloat y) {
    glUniform2f(glGetUniformLocation(mId, name), x, y);
}

void Shader::SetVector2f(GLchar const *name, glm::vec2 const & value) {
    glUniform2f(glGetUniformLocation(mId, name), value.x, value.y);
}

void Shader::SetVector3f(GLchar const *name, GLfloat x, GLfloat y, GLfloat z) {
    glUniform3f(glGetUniformLocation(mId, name), x, y, z);
}

void Shader::SetVector3f(GLchar const *name, glm::vec3 const & value) {
    glUniform3f(glGetUniformLocation(mId, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(GLchar const *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glUniform4f(glGetUniformLocation(mId, name), x, y, z, w);
}

void Shader::SetVector4f(GLchar const *name, glm::vec4 const & value) {
    glUniform4f(glGetUniformLocation(mId, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(GLchar const *name, glm::mat4 const & matrix) {
    glUniformMatrix4fv(glGetUniformLocation(mId, name), 1, GL_FALSE, glm::value_ptr(matrix));
}




