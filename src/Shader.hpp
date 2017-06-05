#pragma once

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
private:
    GLuint mId;

public:
    explicit Shader();

    ~Shader();

    void Use() const;
    void DeleteProgram();
    GLuint const GetId() const;

    GLuint CreateShader(const GLenum shader_type,
                        const std::string &shader_source) const;

    void CreateProgram(const std::string& vertex_shader_code,
                       const std::string& fragment_shader_code);

    void SetFloat    ( GLchar const *name, GLfloat value);
    void SetInteger  ( GLchar const *name, GLint value);
    void SetVector2f ( GLchar const *name, GLfloat x, GLfloat y);
    void SetVector2f ( GLchar const *name, glm::vec2 const &value);
    void SetVector3f ( GLchar const *name, GLfloat x, GLfloat y, GLfloat z);
    void SetVector3f ( GLchar const *name, glm::vec3 const &value);
    void SetVector4f ( GLchar const *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void SetVector4f ( GLchar const *name, glm::vec4 const &value);
    void SetMatrix4  ( GLchar const *name, glm::mat4 const &matrix);

};



