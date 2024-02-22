# Makefile for MSDscript project

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -O2 -g -std=c++11

# Library directory
LIB_DIR = Library_MSDScript

# Source files
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to generate the library file
libmsdscript.a: $(OBJS)
	rm -rf main.o
	ar -ruv libmsdscript.a tests.o expr.o cmdline.o
	rm -rf cmdline.o
	rm -rf expr.o
	rm -rf tests.o
	mv libmsdscript.a Library_MSDScript

# Rule to move the library file to Library_MSDScript directory
move_library: libmsdscript.a | $(LIB_DIR)
	mv $< $(LIB_DIR)

# Rule to generate the binary file "msdscript" from the new library
msdscript: main.cpp $(LIB_DIR)/libmsdscript.a
	$(CXX) $(CXXFLAGS) -o $@ $< -L$(LIB_DIR) -lmsdscript
	
test: msdscript
	./msdscript --test

# Rule to delete all object and binary files
clean:
	rm -rf msdscript $(LIB_DIR)/libmsdscript.a

# PHONY targets
.PHONY: all clean move_library
