#include "io.h"
#include <iostream>
#include <map>
#include <sstream>
#include <glad/glad.h>
#include <chrono>

using namespace Utility::IO;

void Utility::IO::glfwError(int code, const char *description) {
  Logger::instance().log(LOG_SEVERITY_FATAL, description);
}

Logger &Logger::instance() {
  static Logger l;
  return l;
}

void Logger::log(LogSeverity severity, std::string message) {
  if (severity < minSeverity) {
    return;
  } else {
    std::cout << message;
  }

  if (severity == LOG_SEVERITY_FATAL) {
    throw std::exception();
  }
}

std::string Utility::IO::readFile(std::string path) {
  std::fstream f;
  std::stringstream buffer;
  std::string contents;
  std::string line;

  f.open(path, std::ios::in);

  while (getline(f, line)) {
    buffer << line << std::endl;
  }

  contents = buffer.str();

  f.close();

  return contents;
}

std::vector<std::string> Utility::IO::tokenizeString(std::string string,
                                                     char delim) {
  std::stringstream stream(string);
  std::vector<std::string> tokens;

  for (std::string token; std::getline(stream, token, delim);) {
    tokens.push_back(token);
  }

  return tokens;
}
