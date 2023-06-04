#pragma once

#ifdef __unix__
#define OCP_OS_UNIX
#elif defined(_WIN32) || defined(WIN32)
#define OCP_OS_WINDOWS
#endif

#include <iostream>
#include <filesystem>

#ifdef OCP_OS_UNIX
#define OCP_PIPE_ALL_TO_NULL " > /dev/null 2>&1"
#define OCP_TEMP_PATH fs::path("/tmp")
#elif defined(OCP_OS_WINDOWS)
#define OCP_PIPE_ALL_TO_NULL " 1> nul 2> nul"
#define OCP_TEMP_PATH fs::path(getenv("TEMP"))
#endif

#define OCP_LOG(x) std::cerr << __FILE__ << ":" << __LINE__ << ": " #x " = " << (x) << std::endl;

#define OCP_EXERCISES_REPO_LINK "https://github.com/doleckijakub/opencodeprep-exercises"

#define OCP_UNIMPLEMENTED                                                           \
	do                                                                              \
	{                                                                               \
		std::cerr << __FILE__ << ":" << __LINE__ << ": unimplemented" << std::endl; \
		exit(1);                                                                    \
	} while (false)

namespace ocp
{
	namespace fs = ::std::filesystem;

	void info(const char *format, ...);
	void error(const char *format, ...);
	void panic(const char *format, ...);

	char *getenv(const char *name);

	int system_command(std::string cmd, bool quiet = false);

	static fs::path exercises_path = OCP_TEMP_PATH / "opencodeprep" / "exercises";
} // namespace ocp