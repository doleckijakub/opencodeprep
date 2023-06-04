#ifdef __unix__
#define OCP_OS_UNIX
#elif defined(_WIN32) || defined(WIN32)
#define OCP_OS_WINDOWS
#endif

#include <filesystem>
#include <cstdlib>

#ifdef OCP_OS_UNIX
#define OCP_PIPE_ALL_TO_NULL " > /dev/null 2>&1"
#define OCP_TEMP_PATH fs::path("/tmp")
#elif defined(OCP_OS_WINDOWS)
#define OCP_PIPE_ALL_TO_NULL " 1> nul 2> nul"
#define OCP_TEMP_PATH fs::path(getenv("TEMP"))
#endif

#define OCP_UNIMPLEMENTED                                                           \
    do                                                                              \
    {                                                                               \
        std::cerr << __FILE__ << ":" << __LINE__ << ": unimplemented" << std::endl; \
        exit(1);                                                                    \
    } while (false)

namespace ocp
{
#ifdef OCP_OS_UNIX
    char *getenv(const char *name)
    {
        return ::std::getenv(name);
    }
#elif defined(OCP_OS_WINDOWS)
    char *getenv(const char *name)
    {
        static char *value;
        static size_t len;
        if (_dupenv_s(&value, &len, name))
            exit(1);
        return value;
    }
#endif

    namespace fs = ::std::filesystem;
    fs::path exercises_path = OCP_TEMP_PATH / "opencodeprep" / "exercises";
} // namespace ocp