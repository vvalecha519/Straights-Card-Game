CXX=g++ 
CXXFLAGS=-std=c++14 -Wall -O -g -MMD -Werror=vla # use -MMD to generate dependencies
SOURCES = $(wildcard *.cc) # list of all .cc files in the current directory
OBJECTS = ${SOURCES:.cc=.o} # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}  # .d file is list of dependencies for corresponding .cc file
EXEC_TEXT = straights


$(EXEC_TEXT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC_TEXT)

.PHONY: clean 

clean:
	rm $(EXEC_TEXT) $(OBJECTS) $(DEPENDS)

-include ${DEPENDS} # reads the .d files and reruns dependencies
