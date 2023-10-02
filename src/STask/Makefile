CC=g++
CFLAGS=-c -fPIC

TARGET_LIB := libSTask

BUILD_DIR := ./build
SRC_DIR := ./
TEST_DIR := ./test

TARGET_DIR := ../lib
TEST_TARGET_DIR := ../test

LIB_SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
TEST_SRCS := $(shell find $(TEST_DIR) -name '*.cpp')

LIB_OBJS := $(LIB_SRCS:%(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST_SRCS:%(BUILD_DIR)/%.o)

LIB_DEPS := $(LIB_OBJS:.o=.d)
TEST_DEPS := $(TEST_OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)

INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -MMD -MP
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(LIB_DEPS)