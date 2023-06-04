#pragma once

#include "os.hpp"

#include <string>

namespace ocp
{
	namespace LanguageMask
	{
		const static uint32_t NONE = 0;
		const static uint32_t C = (1 << 0);
		const static uint32_t CPP = (1 << 1);
	};

	class Exercise
	{
	private:
		int index;
		::std::string name;
		uint32_t languages;

	public:
		Exercise(const fs::path &);

		friend ::std::ostream &operator<<(::std::ostream &, const Exercise &);
	};

	::std::ostream &operator<<(::std::ostream &, const Exercise &);
} // namespace ocp
