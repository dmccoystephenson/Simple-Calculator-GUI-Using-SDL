CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
# SDL2 + SDL2_image flags (resolved via pkg-config)
SDL_FLAGS = $(shell pkg-config --cflags --libs sdl2 SDL2_image)

all: simpleCalculator testingParsing

# The GUI calculator (requires SDL2 and SDL2_image)
simpleCalculator: simpleCalculator.cpp
	$(CXX) $(CXXFLAGS) simpleCalculator.cpp -o simpleCalculator $(SDL_FLAGS)

# The standalone equation-parser test harness (no SDL dependency)
testingParsing: testingParsing.cpp
	$(CXX) $(CXXFLAGS) testingParsing.cpp -o testingParsing

clean:
	rm -f simpleCalculator testingParsing simpleCalculator.exe testingParsing.exe

.PHONY: all clean
