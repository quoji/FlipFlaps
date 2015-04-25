appname := flipflaps

CXX := g++
CXXFLAGS := -std=c++14

srcfiles := $(shell find . -name "*.C")
objects  := $(patsubst %.C, %.o, $(srcfiles))

all: $(appname)

run: $(appname)
		./flips

#$(appname): $(objects) 
#		$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) -o $(appname) $o(objects) *.cpp find_solution.o -lfltk -lfltk_images

depend: .depend

.depend: $(srcfiles)
		rm -f ./.depend
		$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
		rm -f $(objects)

dist-clean: clean
		rm -f *~ .depend

include .depend