SRC_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(SRC_FILES:.cpp=.o)))
CFLAGS := -g -std=c++11 -I/usr/local/include -I./include
LFLAGS := -L/usr/local/lib
PROG_NAME := checkers

sdl: CFLAGS += -D SDL_GRAPHICS
sdl: LFLAGS += -lSDL2
sdl: all
vulkan: CFLAGS += -D VULKAN_GRAPHICS
vulkan: LFLAGS += -l:libglfw.so.3.3 -lvulkan
vulkan: all

all: $(OBJ_FILES)
	g++ -o $(PROG_NAME) $^ $(LFLAGS)

obj/%.o: src/%.cpp
	g++ $(CFLAGS) -c -o $@ $<

clean:
	rm obj/*.o $(PROG_NAME)
