# Declare all needed variables
# C - compiler; L - linker
CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -O2 -g

LIBS= -lncurses
# Specify the directory for documentation files

# Specify the name of the final executable file (Pacman)
EXECUTABLE=Pacman

DOCDIR=./doc
# Specify the directory for source files
SRCDIR=./src
# Specify the directory for compiled object files
OBJDIR=./src/compiled

# Get all the .cpp files in the source directory
SOURCES=$(wildcard $(SRCDIR)/*.cpp)
# Generate the corresponding object file names by replacing .cpp with .o
# and prepend the object directory path
OBJS=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))


# When we use 'make all' Pacman is the file that will be built
all: compile doc

# Create the compiled directory before compiling the source files
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile the main binary output file - Pacman
# Pacman depends on the object files specified in the variable $(OBJS)
# $^ - represents all the dependencies $(OBJS) == dependency list
compile: $(OBJS)
	$(LD) $(CXXFLAGS) $^ $(LIBS) -o $(EXECUTABLE)

# Specify the pattern rule for object files
# -> match any file ending with .cpp in the $(SRCDIR) directory
#	 and generates an object file in the $(OBJDIR) directory
# compiles each source file ($<) into an object file using the flags specified in $(CXXFLAGS)
# $@ - represents the target name
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to remove all object files, the executable (Pacman), the compiled directory, other generated files, and any other temp files (*~)
# Also clears the leaderboard
clean:
	rm -rf $(OBJDIR) $(EXECUTABLE) *~
	rm -rf $(DOCDIR)
	rm -f Makefile.d
	> ./examples/leaderboard/leaderboard.txt

# Rule to generate dependency information file (using the -MM flag) for the source files
deps:
	$(CXX) -MM $(SRCDIR)/*.cpp > Makefile.d

# Generate the project documentation
doc:
	doxygen Doxyfile

# Run the executable file
run:
	./$(EXECUTABLE)

# Include the generated dependency information from Makefile.d
# '-' ensures that if the Makefile.d file is missing or has an error, it will not cause the Makefile to fail
-include Makefile.d