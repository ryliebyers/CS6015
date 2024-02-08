
# Makefile for MSDscript project

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -O2 -g -std=c++11

# Directories
SRC_DIR = src
DOC_DIR = doc
OBJ_DIR = obj

# Files
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Doxygen configuration file
DOXYFILE = Doxyfile

# Targets
#all: msdscript documentation

msdscript: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


documentation: $(DOXYFILE)
	doxygen $<
	mv html Documentation
	mv latex Documentation
	cd Documentation

documentation2: $(DOXYFILE)
	cd Documentation
	doxygen $<

run: msdscript
	./msdscript
	
test: msdscript
	./msdscript --test

printM:
	@echo "CXX: $(CXX)"
	@echo "CXXFLAGS: $(CXXFLAGS)"
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"

clean:
	rm -rf msdscript $(OBJ_DIR) $(DOC_DIR)


.PHONY: test
