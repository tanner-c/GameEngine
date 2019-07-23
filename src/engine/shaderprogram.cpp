#include "shaderprogram.h"
#include "game/app.h"
#include "io.h"
#include <map>

using namespace Utility::IO;

void Engine::Assets::ShaderProgram::bind() const { glUseProgram(glID); }

void Engine::Assets::ShaderProgram::unbind() const { glUseProgram(0); }

GLuint ShaderProgram::getGLID() const { return glID; }

void ShaderProgram::load() {
  if (loaded) {
    return;
  }

  glID = glCreateProgram();

  vShader->compile();
  fShader->compile();

  glAttachShader(glID, vShader->getGLID());
  glAttachShader(glID, fShader->getGLID());

  glLinkProgram(glID);

  GLint linkSuccessful = 0;
  glGetProgramiv(glID, GL_LINK_STATUS, &linkSuccessful);

  if (linkSuccessful == GL_FALSE) {
    GLint logLength = 0;
    glGetProgramiv(glID, GL_INFO_LOG_LENGTH, &logLength);

    GLchar *infoLog = new GLchar[logLength];
    glGetProgramInfoLog(glID, logLength, &logLength, infoLog);

    auto err = std::string(infoLog);

    err.append("[PATHS: Vertex Shader - ");
    err.append(vShader->path);
    err.append(" / Fragment Shader - ");
    err.append(fShader->path);

    delete[] infoLog;

    Logger::instance().log(LOG_SEVERITY_FATAL, err);
  } else {
    loaded = true;

    glDetachShader(glID, vShader->getGLID());
    glDetachShader(glID, fShader->getGLID());
  }
}

void ShaderProgram::release() { glDeleteProgram(glID); }
