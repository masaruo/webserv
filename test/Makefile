# Compiler
CXX = c++

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -Wextra -pthread -Igoogletest/include

# Google Test and Google Mock libraries
GTEST_LIBS = -Lgoogletest/lib -lgtest -lgtest_main -lgmock -lgmock_main

# Source files
SOURCES = sample_class_test.cpp

# Output executable
TARGET = run_tests

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
