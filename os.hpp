#pragma once

#ifdef __unix__
#define OS_UNIX
#elif defined(_WIN32) || defined(WIN32)
#define OS_WINDOWS
#endif

#ifdef OS_UNIX
#define PIPE_ALL_TO_NULL " > /dev/null 2>&1"
#elif defined(OS_WINDOWS)
#define PIPE_ALL_TO_NULL " 1> nul 2> nul"
#endif