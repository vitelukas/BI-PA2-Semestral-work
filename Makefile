# Declare all needed variables
# C - compiler; L - linker
CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -g
LIBS= -lncurses
# Specify the directory for source files
SRCDIR=./src
# OBJ - variable listing all the object files that need to be created
OBJS= $(SRCDIR)/main.o $(SRCDIR)/CMainMenu.o $(SRCDIR)/CLeaderBoard.o $(SRCDIR)/CGameMode.o $(SRCDIR)/CPlayEasy.o $(SRCDIR)/CPlayMedium.o $(SRCDIR)/CPlayHard.o $(SRCDIR)/CGame.o $(SRCDIR)/CMap.o $(SRCDIR)/CEntity.o $(SRCDIR)/CGhost.o $(SRCDIR)/CGhost_1.o $(SRCDIR)/CGhost_2.o $(SRCDIR)/CGhost_3.o $(SRCDIR)/CPlayer.o

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

# Rule to generate dependency information for the source files
deps:
	$(CXX) -MM $(SRCDIR)/*.cpp > Makefile.d

# Run the executable file
run:
	./Pacman

# Rule to save all the files in the project directory
save:
	@find . -type f -exec touch {} \;

# Include the generated dependency information from Makefile.d
# '-' ensures that if the Makefile.d file is missing or has an error, it will not cause the Makefile to fail
-include Makefile.d