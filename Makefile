CXX = clang++ -std=c++11

APP_INCLUDES:= -I./src/vendors/GLFW -framework Cocoa -framework OpenGL -framework IOKit
APP_LINKER:= -L./src/vendors/GLFW/lib -lglfw3

C_FILES = ${wildcard src/*.cpp} ${wildcard src/Material/*.cpp} ${wildcard src/Model/*.cpp}
TARGET = scope

all:
	$(CXX) $(C_FILES) $(APP_INCLUDES) $(APP_LINKER) -o scope

re: clean all

clean:
	rm -rf scope

.PHONY: all clean
