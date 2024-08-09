# Compiler
CXX = c++

#google test dir to change
GTEST_DIR = googletest

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -pthread -I$(GTEST_DIR)/include $(INC) -ggdb3 -O0

# Google Test and Google Mock libraries
GTEST_LIBS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -lgmock -lgmock_main

# Source files
# SOURCES = $(wildcard ../src/*.cpp) 
# SOURCES := $(shell find ../src -name '*.cpp')
SOURCES := ../src/request/HttpHeaders.cpp
SOURCES := $(filter-out ../src/main.cpp, $(SOURCES))
TESTSRC = \
			HttpHeaders.test.cpp

# Output executable
TARGET = run_tests

INC :=	-I../utility/include \
		-I../include/request \
		-I../include/response \
		-I../include/socket \
		-I../include/utility

ifdef wsl
GTEST_DIR = googletest_wsl2
endif

# Build rule
$(TARGET): $(SOURCES) $(TESTSRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_LIBS)

# Clean rule
clean:
	rm -f $(TARGET)

re: clean
	$(MAKE) $(TARGET)

# Run tests rule
run: $(TARGET)
	./$(TARGET)
	rm -f ./$(TARGET)

.PHONY: clean run
