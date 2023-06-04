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

$(EXEC): *.cpp *.hpp
	$(CPP) $(CPPFLAGS) -o $(EXEC) main.cpp $(LDFLAGS)