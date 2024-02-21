CXX = clang++

APP_INCLUDES:= -I./src/vendors/GLFW -framework Cocoa -framework OpenGL -framework IOKit
APP_LINKER:= -L./src/vendors/GLFW/lib -lglfw3
C_FILES = ./src/*.c*
TARGET = scope

all:
	$(CXX) $(C_FILES) $(APP_INCLUDES) $(APP_LINKER) -o scope

clean:
	rm -rf scope

.PHONY: all clean
