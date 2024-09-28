ifeq ($(OS),Windows_NT)
    output := win_bot.exe
    libs := -lws2_32
    nproc := 6 # set to 6 threads for windows
else
    output := linux_bot
    libs := -lpthread
    nproc := $(shell nproc)  # set to number of cpu threads for linux
endif

MAKEFLAGS += -j$(nproc)

# Object files for current directory
local_objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

# Object files for ../common/ directory
common_objects := $(patsubst ../common/%.cpp,../common/%.o,$(wildcard ../common/*.cpp))

# Combine all objects
objects := $(local_objects) $(common_objects)

# Parallelized build
all: $(output)

$(output): $(objects)
	g++ -std=c++20 $(objects) -Wall $(libs) -o $(output) -O2 -Iinclude -I../common/include
	rm -f $(objects)

# Compile local .cpp files
%.o: %.cpp
	g++ -std=c++20 -c $< -o $@ -Iinclude -I../common/include -O2

# Compile ../common/ .cpp files
../common/%.o: ../common/%.cpp
	g++ -std=c++20 -c $< -o $@ -I../common/include -O2

clean:
	rm -f $(objects) $(output)

.PHONY: all clean
