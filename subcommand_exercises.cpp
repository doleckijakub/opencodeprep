#include "os.hpp"

#include "subcommand_exercises.hpp"
#include "exercise.hpp"

#include <vector>

namespace ocp
{
	using namespace ::std::string_literals;

	namespace exercises
	{
		void exercises_path_validate()
		{
			::std::error_code ec;
			bool exercises_path_exists = fs::exists(exercises_path, ec);
			if (ec)
				panic("failed checking whether directory %s exists, exiting", exercises_path.string().c_str());
			if (!exercises_path_exists)
				panic("directory %s does not exist, exiting", exercises_path.string().c_str());
			if (::std::system(("git -C "s + exercises_path.string() + " status"s + OCP_PIPE_ALL_TO_NULL).c_str()))
				panic("directory %s is not a valid git repo, exiting", exercises_path.string().c_str());
		}

		void pull()
		{
			::std::error_code ec;
			bool exercises_path_exists = fs::exists(exercises_path, ec);
			if (ec)
			{
				panic("failed checking whether directory %s exists, exiting", exercises_path.string().c_str());
			}
			if (!exercises_path_exists)
			{
				fs::create_directories(exercises_path, ec);
				info("directory %s does not exist, creating...", exercises_path.string().c_str());
				if (ec)
				{
					panic("failed creating directory %s, exiting", exercises_path.string().c_str());
				}
			}
			if (system_command("git -C "s + exercises_path.string() + " status"s, true))
			{
				info("directory %s is not a git repo, cleaning...", exercises_path.string().c_str());
				for (auto const &dir_entry : fs::directory_iterator(exercises_path))
				{
					fs::remove_all(dir_entry);
				}
				info("cloning " OCP_EXERCISES_REPO_LINK " to %s ...", exercises_path.string().c_str());
				if (system_command("git -C "s + exercises_path.string() + " clone "s + OCP_EXERCISES_REPO_LINK + " ."))
				{
					panic("failed cloning " OCP_EXERCISES_REPO_LINK ", exiting");
				}
				info("successfully cloned " OCP_EXERCISES_REPO_LINK);
			}
			info("pulling " OCP_EXERCISES_REPO_LINK " to %s ...", exercises_path.string().c_str());
			if (system_command("git -C "s + exercises_path.string() + " pull origin master"s))
			{
				panic("failed pulling, exiting");
			}
			info("pulling successfull");
		}

		void list(/* ListOptions &options */)
		{
			exercises_path_validate();

			::std::vector<Exercise> exercises;

			for (auto const &entry : fs::directory_iterator(exercises_path))
			{
				if (entry.path().filename().string()[0] == '.')
					continue;
				if (entry.path().filename() == "README.md")
					continue;
				if (entry.path().filename() == "CONTRIBUTING.md")
					continue;

				exercises.emplace_back(entry.path());
			}

			for (auto const &exercise : exercises)
			{
				std::cout << exercise << std::endl;
			}
		}
	} // namespace exercises

} // namespace ocp
