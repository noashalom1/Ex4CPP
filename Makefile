# Compiler and flags
CXX = g++  
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude --coverage

# Source and test files
SRC = Demo.cpp
TESTS = tests/tests.cpp
INCLUDES = include/MyContainer.hpp \
           include/iterators/AscendingOrder.hpp \
           include/iterators/DescendingOrder.hpp \
           include/iterators/SideCrossOrder.hpp \
           include/iterators/ReverseOrder.hpp \
           include/iterators/RegularOrder.hpp \
           include/iterators/MiddleOutOrder.hpp \
           include/iterators/AbstractIterator.hpp

# Output executables
MAIN_EXEC = Main
TEST_EXEC = Test

# Default target
all: $(MAIN_EXEC)

# Build main demo and run it
$(MAIN_EXEC): $(SRC) $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(MAIN_EXEC)
	./$(MAIN_EXEC)

# Build and run tests
test: $(TESTS) $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(TESTS) -o $(TEST_EXEC)
	./$(TEST_EXEC)

# Valgrind memory check
valgrind: $(TESTS) $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(TESTS) -o $(TEST_EXEC)
	valgrind --leak-check=full ./$(TEST_EXEC)

# Coverage only on tests
coverage:
	rm -f *.gcno *.gcda *.gcov Test
	$(CXX) $(CXXFLAGS) --coverage $(TESTS) -o $(TEST_EXEC)
	./$(TEST_EXEC) > /dev/null
	@echo "====== GCOV COVERAGE SUMMARY ======"
	@gcov -b -c -o . Test-tests.gcno
	@echo "\nTop Coverage Summary:"
	@grep -E 'File|Lines executed' *.gcov | paste - - | column -t

# Clean up generated files
clean:
	rm -f $(MAIN_EXEC) $(TEST_EXEC) *.gcno *.gcda *.gcov Test
