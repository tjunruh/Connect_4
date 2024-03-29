
CXX := g++

EXECUTABLE ?= connect4

SRC_DIR ?= code
BLD_DIR ?= build
INC_DIR := $(shell find $(SRC_DIR) -type d)

SRCS := $(shell find $(SRC_DIR) -name *.cpp)
OBJS := $(SRCS:%=$(BLD_DIR)/%.o)
DEPS := $(OCJS:.o=.d)

LDFLAGS := -lncurses
INC_FLAGS := $(addprefix -I,$(INC_DIR))
CXXFLAGS := -std=c++17 $(LDFLAGS) -O2 $(INC_FLAGS) -Wall -MMD -MP

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BLD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -r $(BLD_DIR)
	-rm $(EXECUTABLE)

-include $(DEPS)