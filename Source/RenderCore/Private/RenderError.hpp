#pragma once

#ifdef SPY_DEBUG
#include "BaseTypes.hpp"
#include "glad/glad.h"

#include <assert.h>
#include <string>
#include <iostream>

namespace spy
{
namespace priv
{
static void CheckRenderError(const char* file, int32 line)
{
    GLenum err(glGetError());

    while (err != GL_NO_ERROR)
    {
        std::string error;
        switch (err)
        {
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        }
        std::cout << "GL_" << error.c_str() << " - " << file << ":" << line << std::endl;
        err = glGetError();
        assert(false);
    }
}
} // namespace priv
} // namespace spy

#define SPY_CHECK_RENDER_ERROR() spy::priv::CheckRenderError(__FILE__, __LINE__)

#else

#define SPY_CHECK_RENDER_ERROR();

#endif