#include "os.hpp"
#include "exercises.hpp"

namespace ocp
{
	using namespace std::string_literals;

	namespace exercises
	{
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
				for (auto const &dir_entry : std::filesystem::directory_iterator(exercises_path))
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

		void list()
		{
			OCP_UNIMPLEMENTED;
		}
	} // namespace exercises

} // namespace ocp
