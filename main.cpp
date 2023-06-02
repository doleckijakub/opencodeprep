#include "os.hpp"

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstdarg>

namespace opencodeprep
{
	void panic(const char *format, ...)
	{
		std::cerr << "fatal error: ";
		va_list va;
		va_start(va, format);
		std::vfprintf(stderr, format, va);
		va_end(va);
		std::cerr << std::endl;
		exit(1);
	}
}

int main(int argc, const char **argv)
{
	auto next_arg = [&argc, &argv]() -> const char *
	{
		assert(argc);
		const char *arg = *argv;
		--argc;
		++argv;
		return arg;
	};

	const char *program_name = next_arg();

	bool git_installed = std::system("git version" PIPE_ALL_TO_NULL) == 0;

	if (!git_installed)
	{
		opencodeprep::panic("git is not installed, but is a necessary prerequisite. Check https://github.com/git-guides/install-git for an installation guide.");
	}

	return 0;
}