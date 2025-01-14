CC = g++
CPPFLAGS = -I.
CFLAGS = -Wall -std=c++11 -pedantic -g

BUILD_DIR = build/$(shell uname -s)-$(shell uname -m)
LIB_DIR = lib/$(shell uname -s)-$(shell uname -m)
BIN_DIR = bin/$(shell uname -s)-$(shell uname -m)

COMPILE_TARGETS = $(LIB_DIR)/particle_engine.a

all: $(COMPILE_TARGETS)

clean:
	rm -rf build/ lib/ bin/ 

$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)

$(LIB_DIR) :
	mkdir -p $(LIB_DIR)

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)

OBJECTS = $(BUILD_DIR)/Grid.o\
		  $(BUILD_DIR)/GridSection.o\
		  $(BUILD_DIR)/Particle.o\
		  $(BUILD_DIR)/ParticleSimulation.o

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIB_DIR)/particle_engine.a: $(OBJECTS) | $(LIB_DIR)
	ar rcs $@ $^
