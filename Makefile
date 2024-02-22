CXX = clang++ -std=c++11 -w

APP_INCLUDES:= -I./src/vendors/GLFW -framework Cocoa -framework OpenGL -framework IOKit
APP_LINKER:= -L./src/vendors/GLFW/lib -lglfw3

CPP_FILES = ${wildcard src/*.cpp} ${wildcard src/Texture/*.cpp} ${wildcard src/Model/*.cpp} ${wildcard src/Shader/*.cpp}
C_FILES = ./src/vendors/glad/glad.c

TARGET = scope

all:
	$(CXX) $(C_FILES) $(CPP_FILES) $(APP_INCLUDES) $(APP_LINKER) -o scope

clean:
	rm -rf scope

.PHONY: all clean
