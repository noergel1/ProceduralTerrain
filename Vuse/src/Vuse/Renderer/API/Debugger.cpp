#include "vuse_pch.h"
#include "Debugger.h"

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
    GLsizei length, const char* message, const void* userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::stringstream debugMessage;

    debugMessage << "---------------" << std::endl;
    debugMessage << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             debugMessage << "Source: API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   debugMessage << "Source: Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: debugMessage << "Source: Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     debugMessage << "Source: Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     debugMessage << "Source: Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           debugMessage << "Source: Other"; break;
    } debugMessage << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               debugMessage << "Type: Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: debugMessage << "Type: Deprecated Behaviour"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  debugMessage << "Type: Undefined Behaviour"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         debugMessage << "Type: Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         debugMessage << "Type: Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              debugMessage << "Type: Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          debugMessage << "Type: Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           debugMessage << "Type: Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               debugMessage << "Type: Other"; break;
    } debugMessage << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         debugMessage << "Severity: high"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       debugMessage << "Severity: medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          debugMessage << "Severity: low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: debugMessage << "Severity: notification"; break;
    } debugMessage << std::endl;
    debugMessage << std::endl;

    VUSE_CORE_WARN( debugMessage.str() );
}