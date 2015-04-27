appname := flipflaps

CXX := g++
CXXFLAGS := -std=c++14

srcfiles := $(shell find . -name "*.C")
objects  := $(patsubst %.C, %.o, $(srcfiles))

all: $(appname)
	$(CXX) $(CXXFLAGS) *.cpp find_solution.o -lfltk -lfltk_images

run: $(appname)
	$(CXX) $(CXXFLAGS) *.cpp find_solution.o -lfltk -lfltk_images
	./a.out

$(appname):
	$(CXX) $(CXXFLAGS) *.cpp find_solution.o -lfltk -lfltk_images