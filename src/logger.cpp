#include "logger.h"
#include <iostream>

void ClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

bool LogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::string error_string = "UNKNOWN";
        switch (error) {
            case GL_INVALID_ENUM:
                error_string = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error_string = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error_string = "GL_INVALID_OPERATION";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error_string = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                error_string = "GL_OUT_OF_MEMORY";
                break;
            default:;
        }

        if (file == nullptr || *file == 0)
            std::cerr << "[OpenGl Error] (" << error_string << ")" << std::endl;
        else
            std::cerr << "[OpenGl Error] (" << error_string << ")" <<
                      " " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}