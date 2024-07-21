SRC_DIR = src
ODIR = obj
IDIR = include
BUILD_DIR = build

BIN = pwmctl

CC = g++
CXXFLAGS = -I$(IDIR) -Werror -Wall -Wextra
LDFLAGS =

_DEPS = pwmctl.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o pwmctl.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.SECONDEXPANSION:

$(ODIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS) | $$(@D)
	$(CC) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS)

$(BUILD_DIR)/$(BIN): $(OBJ) | $$(@D)
	$(CC) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $@

$(ODIR):
	mkdir -p $@

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BUILD_DIR)/$(BIN)
