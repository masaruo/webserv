# Compiler
CXX = c++

#google test dir to change
GTEST_DIR = googletest

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -Wextra -pthread -I$(GTEST_DIR)/include

# Google Test and Google Mock libraries
GTEST_LIBS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -lgmock -lgmock_main

# Source files
SOURCES = sample_class_test.cpp

# Output executable
TARGET = run_tests

ifdef wsl
GTEST_DIR = googletest_wsl2
endif

# Build rule
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(GTEST_LIBS)

# Clean rule
clean:
	rm -f $(TARGET)

# Run tests rule
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
