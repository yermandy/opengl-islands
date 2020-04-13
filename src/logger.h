#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __builtin_debugtrap()

#define CHECK_GL_ERROR() ClearErrors(); ASSERT(LogCall(nullptr, __FILE__, __LINE__))

#define DEBUG = 1

#ifdef DEBUG
    #define LOG(x) ClearErrors(); x; ASSERT(LogCall(#x, __FILE__, __LINE__))
#else
    #define LOG(x) x
#endif

void ClearErrors();

bool LogCall(const char* function, const char* file, int line);

