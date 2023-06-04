CPP := clang++
CPPFLAGS := -Wall -Wextra -pedantic -std=c++17
LDFLAGS :=

EXEC := ocp

ifeq ($(OS),Windows_NT)
	WINDOWS := 1
	EXEC := ocp.exe
else ifeq ($(shell uname),Linux)
	LINUX := 1
else ifeq ($(shell uname),Darwin)
	MACOS := 1
else
	$(error Unsupported platform: $(shell uname))
endif

all: $(EXEC)

os.o: os.hpp os.cpp
	$(CPP) -c $(CPPFLAGS) -o os.o os.cpp

exercises.o: exercises.hpp exercises.cpp
	$(CPP) -c $(CPPFLAGS) -o exercises.o exercises.cpp

$(EXEC): *.cpp *.hpp os.o exercises.o
	$(CPP) $(CPPFLAGS) -o $(EXEC) os.o exercises.o main.cpp $(LDFLAGS)