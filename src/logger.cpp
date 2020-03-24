#include "logger.h"
#include <iostream>

void ClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

bool LogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cerr << "[OpenGl Error] (" << std::hex << error << std::dec << ")" <<
                  " " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}