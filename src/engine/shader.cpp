#include "shader.h"
#include <vector>

using namespace Utility::IO;
using namespace Engine::Assets;

Shader::~Shader() { glDeleteShader(glID); }

void Shader::compile() {
  glID = glCreateShader(type);
  auto sourceCStr = (const GLchar *) source.c_str();
  glShaderSource(glID, 1, &sourceCStr, 0);
  glCompileShader(glID);

  GLint compileSuccessful = 0;
  glGetShaderiv(glID, GL_COMPILE_STATUS, &compileSuccessful);

  if (compileSuccessful == GL_FALSE) {
    GLint logLength = 0;
    glGetShaderiv(glID, GL_INFO_LOG_LENGTH, &logLength);

    GLchar *infoLog = new GLchar[logLength];
    glGetShaderInfoLog(glID, logLength, &logLength, infoLog);

    glDeleteShader(glID);

    auto err = std::string(infoLog);

    delete[] infoLog;

    err.append(" [PATH: ");
    err.append(path);
    err.append("]");

    Logger::instance().log(LOG_SEVERITY_FATAL, err);
  } else {
    compiled = true;
  }
}

bool Shader::isCompiled() const { return compiled; }

GLuint Shader::getGLID() const { return glID; }
