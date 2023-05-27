CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -g
LIBS= -lncurses
SRCDIR=./src
OBJS= $(SRCDIR)/main.o $(SRCDIR)/CMainMenu.o $(SRCDIR)/CLeaderBoard.o $(SRCDIR)/CGameMode.o $(SRCDIR)/CPlayEasy.o $(SRCDIR)/CPlayMedium.o $(SRCDIR)/CPlayHard.o $(SRCDIR)/CGame.o $(SRCDIR)/CMap.o $(SRCDIR)/CEntity.o $(SRCDIR)/CGhost_1.o $(SRCDIR)/CGhost_2.o $(SRCDIR)/CGhost_3.o $(SRCDIR)/CPlayer.o

all: Pacman

Pacman: $(OBJS)
	$(LD) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(SRCDIR)/*.o Pacman *~

deps:
	$(CXX) -MM $(SRCDIR)/*.cpp > Makefile.d

-include Makefile.d