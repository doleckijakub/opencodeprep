#include "os.hpp"

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstdarg>

namespace ocp
{
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

	enum class Option : uint32_t
	{
		NONE = 0,
		HELP = (1 << 0),
		EXERCISE = (1 << 1),
		EXERCISES = (1 << 2),
		ALL = (uint32_t)-1
	};

	uint32_t operator&(const Option &a, const Option &b)
	{
		return ((uint32_t)a) & ((uint32_t)b);
	}

	void usage(const std::string &program_name, std::ostream &sink, Option option = Option::ALL)
	{
		auto next_usage = [&]() -> std::ostream &
		{
			static bool already_called = false;
			sink << (already_called ? "       " : "Usage: ") << program_name << " ";
			already_called = true;
			return sink;
		};

		if (option & Option::HELP)
			next_usage() << "help                            - prints this message" << std::endl;
		if (option == Option::EXERCISE)
			next_usage() << "exercise help                   - prints this message" << std::endl;
		if (option & Option::EXERCISE)
		{
			next_usage() << "exercise start <exercise name>  - sets up the environment for a given exercise" << std::endl;
			next_usage() << "exercise run                    - compiles/interprets your code, runs it and checks validity with testcases" << std::endl;
			next_usage() << "exercise submit                 - same as run but with more testcases" << std::endl;
		}
		if (option == Option::EXERCISES)
			next_usage() << "exercises help                  - prints this message" << std::endl;
		if (option & Option::EXERCISES)
		{
			next_usage() << "exercises pull                  - pulls the exercise list from https://github.com/doleckijakub/opencodeprep-exercises to " << ocp::exercises_path.string() << std::endl;
			next_usage() << "exercises list                  - lists exercises from " << std::endl;
		}
	}
}

int main(int argc, const char **argv)
{
	auto next_arg = [&]() -> const char *
	{
		assert(argc);
		const char *arg = *argv;
		--argc;
		++argv;
		return arg;
	};

	std::string program_name = next_arg();

	{
		bool git_installed = std::system("git version" OCP_PIPE_ALL_TO_NULL) == 0;

		if (!git_installed)
			ocp::panic("git is not installed, but is a necessary prerequisite. Check https://github.com/git-guides/install-git for an installation guide.");
	}

	if (!argc)
	{
		ocp::error("missing options");
		ocp::usage(program_name, std::cerr);
		return 1;
	}

	std::string arg = next_arg();
	if (arg == "help")
	{
		ocp::usage(program_name, std::cerr);
		return 0;
	}
	else if (arg == "exercise")
	{
		if (!argc)
		{
			ocp::error("missing options");
			ocp::usage(program_name, std::cerr, ocp::Option::EXERCISE);
			return 1;
		}

		std::string arg = next_arg();
		if (arg == "help")
		{
			ocp::usage(program_name, std::cerr, ocp::Option::EXERCISE);
		}
		else if (arg == "start")
		{
			if (!argc)
			{
				ocp::panic("missing exercise name");
			}

			std::string exercise_name = next_arg();
			OCP_UNIMPLEMENTED;
		}
		else if (arg == "run")
		{
			OCP_UNIMPLEMENTED;
		}
		else if (arg == "submit")
		{
			OCP_UNIMPLEMENTED;
		}
		else
		{
			ocp::panic("bad option: '%s'", arg.c_str());
		}
	}
	else if (arg == "exercises")
	{
		if (!argc)
		{
			ocp::error("missing options");
			ocp::usage(program_name, std::cerr, ocp::Option::EXERCISES);
			return 1;
		}

		std::string arg = next_arg();
		if (arg == "help")
		{
			ocp::usage(program_name, std::cerr, ocp::Option::EXERCISES);
		}
		else if (arg == "pull")
		{
			OCP_UNIMPLEMENTED;
		}
		else if (arg == "list")
		{
			OCP_UNIMPLEMENTED;
		}
		else
		{
			ocp::panic("bad option: '%s'", arg.c_str());
		}
	}
	else
	{
		ocp::error("bad option: '%s'", arg.c_str());
		ocp::usage(program_name, std::cerr);
		return 1;
	}

	return 0;
}