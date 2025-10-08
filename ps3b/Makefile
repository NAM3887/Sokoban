CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# .hpp files
DEPS = Sokoban.hpp
# Compiled .o files
OBJECTS = Sokoban.o
# The name program
PROGRAM = Sokoban

.PHONY: all clean lint 

all: $(PROGRAM) Sokoban.a test

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

Sokoban.a:
	ar rcs Sokoban.a $(OBJECTS)

test: test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
clean:
	rm -f *.o *.a $(PROGRAM) test

lint:
	cpplint *.cpp *.hpp
