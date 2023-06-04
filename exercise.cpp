#include "exercise.hpp"

#include <sstream>
#include <cassert>

namespace ocp
{
	Exercise::Exercise(const fs::path &path)
	{
		::std::string filename = path.filename().string();
		::std::istringstream ss(filename);
		{
			::std::string token;
			std::getline(ss, token, '-');
			index = ::std::stoi(token);
			std::getline(ss, token, '-');
			name = token;
			while (std::getline(ss, token, '-'))
			{
				name += '-';
				name += token;
			}
		}
		languages = LanguageMask::NONE;
		if (fs::exists(path / "c"))
			languages |= LanguageMask::C;
		if (fs::exists(path / "cpp"))
			languages |= LanguageMask::CPP;
	}

	::std::string languages_to_string(const uint32_t &languages)
	{
		::std::string ret;
		int count = 0;
		if (languages & LanguageMask::C)
		{
			if (count++)
				ret += ",";
			ret += "c";
		}
		if (languages & LanguageMask::CPP)
		{
			if (count++)
				ret += ",";
			ret += "cpp";
		}
		assert(count);
		return ret;
	}

	::std::ostream &operator<<(::std::ostream &out, const Exercise &exercise)
	{
		out << exercise.index << "\t";
		out << exercise.name << "\t";
		out << languages_to_string(exercise.languages);
		return out;
	}
} // namespace ocp
