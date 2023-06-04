CPP := clang++
CPPFLAGS := -Wall -Wextra -pedantic -std=c++17
LDFLAGS :=

EXEC := ocp

ifeq ($(OS),Windows_NT)
	WINDOWS := 1
else ifeq ($(shell uname),Linux)
	LINUX := 1
else ifeq ($(shell uname),Darwin)
	MACOS := 1
else
	$(error Unsupported platform: $(shell uname))
endif
ifeq ($(WINDOWS),1)
	EXEC := ocp.exe
else ifeq ($(LINUX),1)
else ifeq ($(MACOS),1)
	CPPFLAGS := -std=c++17
else
	$(error unreachable)
endif

all: $(EXEC)

os.o: os.hpp os.cpp
	$(CPP) -c $(CPPFLAGS) -o os.o os.cpp

subcommand_exercises.o: subcommand_exercises.hpp subcommand_exercises.cpp
	$(CPP) -c $(CPPFLAGS) -o subcommand_exercises.o subcommand_exercises.cpp

exercise.o: exercise.hpp exercise.cpp
	$(CPP) -c $(CPPFLAGS) -o exercise.o exercise.cpp

$(EXEC): *.cpp *.hpp os.o exercise.o subcommand_exercises.o
	$(CPP) $(CPPFLAGS) -o $(EXEC) os.o exercise.o subcommand_exercises.o main.cpp $(LDFLAGS)