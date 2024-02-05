CXX = clang

SRC_DIR = src
BUILD_DIR = build

APP_INCLUDES:= -I./src/vendors/GLFW -framework Cocoa -framework OpenGL -framework IOKit
APP_LINKER:= -L./src/vendors/GLFW/lib -lglfw3

# Obtenez tous les fichiers source CPP dans le répertoire source
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

C_FILES = ./src/*.cpp
# Générez la liste des fichiers objets dans le répertoire de construction
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Nom de l'exécutable final
TARGET = scope

all: $(TARGET)

# Règle pour créer l'exécutable final
$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

# Règle générique pour compiler les fichiers source en fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
build:
	$(CXX) $(C_FILES) $(APP_INCLUDES) $(APP_LINKER)

clean:
	rm -rf $(BUILD_DIR) scope

.PHONY: all clean
