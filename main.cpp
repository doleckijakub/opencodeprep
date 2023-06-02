#include <iostream>
#include <cassert>

int main(int argc, const char **argv)
{
    auto next_arg = [&argc, &argv]() -> const char* {
        assert(argc);
        const char *arg = *argv;
        --argc;
        ++argv;
        return arg;
    };

    const char *program_name = next_arg();

    std::cout << program_name << std::endl;
    return 0;
}