#include "shaderprogram.h"
#include "game/app.h"
#include "utilities/io.h"
#include <map>

using namespace Utility::IO;
using namespace Engine::Assets;

void ShaderProgram::bind() const { glUseProgram(glID); }

void ShaderProgram::unbind() const { glUseProgram(0); }

GLuint ShaderProgram::getGLID() const { return glID; }

void ShaderProgram::load() {
  //TODO: Allow for more than just vert/frag pairs
  std::ostringstream versionStatement,
                     fragPath,
                     vertPath;
  
  int minorVer = GLVersion.minor;
  
  // Add a zero to the end of the minor version
  if (minorVer < 9) {
    minorVer *= 10;
  }

  versionStatement << "\n#version " << GLVersion.major << minorVer << " core\n";
  
  vertPath << path << VERTEX_SHADER_EXT;
  fragPath << path << FRAGMENT_SHADER_EXT;
  
  auto vertSource = readFile(vertPath.str());
  auto fragSource = readFile(fragPath.str());
  
  vertSource.insert(0, versionStatement.str());
  fragSource.insert(0, versionStatement.str());
  
  auto vertID = compileShader(vertSource, SHADER_TYPE_VERTEX);
  auto fragID = compileShader(fragSource, SHADER_TYPE_FRAGMENT);
  
  linkProgram(vertID, fragID);
}

GLuint ShaderProgram::compileShader(const std::string& source, ShaderType type) {
  auto glID = glCreateShader(type);
  
  auto versionStatement = std::ostringstream() << "#version 400 core\n";
  
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
  }
  
  return glID;
}

void ShaderProgram::linkProgram(GLuint vShader, GLuint fShader) {
  if (loaded) {
    return;
  }
  
  glID = glCreateProgram();
  
  glAttachShader(glID, vShader);
  glAttachShader(glID, fShader);
  
  glLinkProgram(glID);
  
  GLint linkSuccessful = 0;
  glGetProgramiv(glID, GL_LINK_STATUS, &linkSuccessful);
  
  if (linkSuccessful == GL_FALSE) {
    GLint logLength = 0;
    glGetProgramiv(glID, GL_INFO_LOG_LENGTH, &logLength);
    
    GLchar *infoLog = new GLchar[logLength];
    glGetProgramInfoLog(glID, logLength, &logLength, infoLog);
    
    Logger::instance().log(LOG_SEVERITY_FATAL, std::string(infoLog));
    
    delete[] infoLog;
    
  } else {
    loaded = true;
    
    glDetachShader(glID, vShader);
    glDetachShader(glID, fShader);
    glDeleteShader(vShader);
    glDeleteShader(fShader);
  }
}

void ShaderProgram::release() { glDeleteProgram(glID); }
