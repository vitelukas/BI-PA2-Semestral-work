# Declare all needed variables
# C - compiler; L - linker
CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -O2 -g
LIBS= -lncurses
# Specify the directory for source files
SRCDIR=./src
# Get all the .cpp files in the source directory
SOURCES=$(wildcard $(SRCDIR)/*.cpp)
# Generate the corresponding object file names by replacing .cpp with .o
OBJS=$(SOURCES:.cpp=.o)


# When we use 'make all' Pacman is the file tha will be build
all: Pacman

# Compile the main binary output file - Pacman
# Pacman depends on the object files specified in the variable $(OBJS)
# $@ - represents the target name (Pacman)
# $^ - represents all the dependencies $(OBJS)
Pacman: $(OBJS)
	$(LD) $(CXXFLAGS) -o $@ $^ $(LIBS) 

# Specify the patter rule for object files
# -> match any file ending with .cpp in the $(SRCDIR) directory
#	 and generates an object file in the same directory
# compiles each source file ($<) into an object file ($@) using the flags specified in $(CXXFLAGS)
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to remove all object files, the executable (Pacman), and any other temp files (*~)
# Also clears the leaderboard
clean:
	rm -f $(SRCDIR)/*.o Pacman *~
	> ./examples/leaderboard/leaderboard.txt

# Rule to generate dependency informations flie (using the -MM flag) for the source files
deps:
	$(CXX) -MM $(SRCDIR)/*.cpp > Makefile.d

# Generate the project documentation
doc:
	doxygen Doxyfile

# Run the executable file
run:
	./Pacman

# Rule to save all the files in the project directory
save:
	@find . -type f -exec touch {} \;

# Include the generated dependency information from Makefile.d
# '-' ensures that if the Makefile.d file is missing or has an error, it will not cause the Makefile to fail
-include Makefile.d