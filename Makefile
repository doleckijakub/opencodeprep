CPP := g++
CPPFLAGS := -Wall -Wextra -pedantic
LDFLAGS :=

ifeq ($(OS),Windows_NT)
	WINDOWS := 1
else ifeq ($(shell uname),Linux)
	LINUX := 1
else ifeq ($(shell uname),Darwin)
	MACOS := 1
else
	$(error Unsupported platform: $(shell uname))
endif

all: opencodeprep

opencodeprep: main.cpp
	$(CPP) $(CPPFLAGS) -o opencodeprep main.cpp $(LDFLAGS)