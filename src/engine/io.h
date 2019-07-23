#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>

namespace Utility {
namespace IO {
void glfwError(int code, const char *description);
void GLAPIENTRY
glMessage(GLenum
source,
GLenum type, GLuint
id,
GLenum severity,
    GLsizei
length,
const GLchar *message,
const void *userParam
);

std::string readFile(std::string path);
std::vector<std::string> tokenizeString(std::string string, char delim);

enum LogSeverity {
  LOG_SEVERITY_VERBOSE,
  LOG_SEVERITY_NORMAL,
  LOG_SEVERITY_WARNING,
  LOG_SEVERITY_ERROR,
  LOG_SEVERITY_FATAL
};

class Logger {
 protected:
  LogSeverity minSeverity;

 public:
  ~Logger() {};
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;
  static Logger &instance();

  void log(LogSeverity severity, std::string message);

 private:
#ifdef NDEBUG
  Logger() : minSeverity{LOG_SEVERITY_NORMAL};
#else
  Logger()
      : minSeverity{LOG_SEVERITY_VERBOSE} {};
#endif
};
} // namespace IO
}; // namespace Utility