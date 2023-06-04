#include "os.hpp"
#include "subcommand_exercises.hpp"

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string>

namespace ocp
{
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
			sink << (already_called ? "   or: " : "usage: ") << program_name << " ";
			already_called = true;
			return sink;
		};

		// auto next_option = [&]() -> std::ostream &
		// {
		// 	static std::string spaces = std::string(7, ' ');
		// 	sink << spaces;
		// 	return sink;
		// };

		if (option & Option::HELP)
			next_usage() << "help                              - prints this message" << std::endl;
		if (option == Option::EXERCISE)
			next_usage() << "exercise help                     - prints this message" << std::endl;
		if (option & Option::EXERCISE)
		{
			next_usage() << "exercise attempt <exercise name>  - sets up the environment for a given exercise" << std::endl;
			next_usage() << "exercise run                      - compiles/interprets your code, runs it and checks validity with testcases" << std::endl;
			next_usage() << "exercise submit                   - same as run but with more testcases" << std::endl;
		}
		if (option == Option::EXERCISES)
			next_usage() << "exercises help                    - prints this message" << std::endl;
		if (option & Option::EXERCISES)
		{
			next_usage() << "exercises pull                    - updates the exercise list" << std::endl;
			next_usage() << "exercises list                    - lists downloaded exercises" << std::endl;
			// next_usage() << "exercises list [options]          - lists downloaded exercises" << std::endl;
			// next_option() << "options:" << std::endl;
			// exercises::ListOptions list_options;
			// next_option() << "--results-per-page <number>  - changes the amount of results visible at once, default = " << list_options.results_per_page << std::endl;
			// next_option() << "--page <number>              - changes the page number, default = " << list_options.page << std::endl;
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
			ocp::panic("git is not installed, but is a necessary prerequisite. Install it to continue.");
	}

	{
		bool make_installed = std::system("make --version" OCP_PIPE_ALL_TO_NULL) == 0;

		if (!make_installed)
			ocp::panic("GNU Make is not installed, but is a necessary prerequisite. Install it to continue.");
	}

	if (!argc)
	{
		ocp::error("missing subcommand");
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
		else if (arg == "attempt")
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
			ocp::panic("unknown subcommand: '%s'", arg.c_str());
		}
	}
	else if (arg == "exercises")
	{
		if (!argc)
		{
			ocp::error("missing subcommand");
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
			ocp::exercises::pull();
		}
		else if (arg == "list")
		{
			// ocp::exercises::ListOptions options;
			// while (argc)
			// {
			// 	std::string arg = next_arg();
			// 	if (arg == "--results-per-page")
			// 	{
			// 		if (!argc)
			// 		{
			// 			ocp::panic("missing number after '%s'", arg.c_str());
			// 		}
			// 		std::string num = next_arg();
			// 		try
			// 		{
			// 			options.results_per_page = std::stoi(num);
			// 		}
			// 		catch (std::invalid_argument const &e)
			// 		{
			// 			ocp::panic("not a number '%s'", arg.c_str());
			// 		}
			// 		catch (std::out_of_range const &e)
			// 		{
			// 			ocp::panic("integer overflow, number '%s', is too big", arg.c_str());
			// 		}
			// 	}
			// 	else if (arg == "--page")
			// 	{
			// 		if (!argc)
			// 		{
			// 			ocp::panic("missing number after '%s'", arg.c_str());
			// 		}
			// 		std::string num = next_arg();
			// 		try
			// 		{
			// 			options.page = std::stoi(num);
			// 		}
			// 		catch (std::invalid_argument const &e)
			// 		{
			// 			ocp::panic("not a number '%s'", arg.c_str());
			// 		}
			// 		catch (std::out_of_range const &e)
			// 		{
			// 			ocp::panic("integer overflow, number '%s', is too big", arg.c_str());
			// 		}
			// 	}
			// 	else
			// 	{
			// 		ocp::panic("unknown subcommand: '%s'", arg.c_str());
			// 	}
			// }
			ocp::exercises::list(/* options */);
		}
		else
		{
			ocp::panic("unknown subcommand: '%s'", arg.c_str());
		}
	}
	else
	{
		ocp::error("unknown subcommand: '%s'", arg.c_str());
		ocp::usage(program_name, std::cerr);
		return 1;
	}

	return 0;
}