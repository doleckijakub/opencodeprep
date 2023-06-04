#include "os.hpp"

#include <cstdlib>
#include <cstdarg>

namespace ocp
{
	void info(const char *format, ...)
	{
		std::cerr << "info: ";
		va_list va;
		va_start(va, format);
		std::vfprintf(stderr, format, va);
		va_end(va);
		std::cerr << std::endl;
	}

	void error(const char *format, ...)
	{
		std::cerr << "error: ";
		va_list va;
		va_start(va, format);
		std::vfprintf(stderr, format, va);
		va_end(va);
		std::cerr << std::endl;
	}

	void panic(const char *format, ...)
	{
		std::cerr << "error: ";
		va_list va;
		va_start(va, format);
		std::vfprintf(stderr, format, va);
		va_end(va);
		std::cerr << std::endl;
		exit(1);
	}

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
			panic("failed reading environmantal variable: '%s'", name);
		return value;
	}
#endif

	int system_command(std::string cmd, bool quiet)
	{
		info("running command: '%s'", cmd.c_str());
		if (quiet)
			cmd += OCP_PIPE_ALL_TO_NULL;
		return ::std::system(cmd.c_str());
	}

} // namespace ocp
