CEntity.o: src/CEntity.cpp src/CEntity.hpp src/CMap.hpp
CGame.o: src/CGame.cpp src/CGame.hpp src/CMap.hpp src/CPlayer.hpp \
 src/CEntity.hpp src/CGhost_1.hpp src/CGhost.hpp src/CGhost_2.hpp \
 src/CGhost_3.hpp
CGameMode.o: src/CGameMode.cpp
CGhost.o: src/CGhost.cpp src/CGhost.hpp src/CEntity.hpp src/CMap.hpp \
 src/CPlayer.hpp
CGhost_1.o: src/CGhost_1.cpp src/CGhost_1.hpp src/CGhost.hpp \
 src/CEntity.hpp src/CMap.hpp src/CPlayer.hpp
CGhost_2.o: src/CGhost_2.cpp src/CGhost_2.hpp src/CGhost.hpp \
 src/CEntity.hpp src/CMap.hpp src/CPlayer.hpp
CGhost_3.o: src/CGhost_3.cpp src/CGhost_3.hpp src/CGhost.hpp \
 src/CEntity.hpp src/CMap.hpp src/CPlayer.hpp
CLeaderBoard.o: src/CLeaderBoard.cpp src/CLeaderBoard.hpp
CMainMenu.o: src/CMainMenu.cpp src/CMainMenu.hpp src/CLeaderBoard.hpp \
 src/CGameMode.hpp src/CGame.hpp src/CMap.hpp src/CPlayer.hpp \
 src/CEntity.hpp src/CGhost_1.hpp src/CGhost.hpp src/CGhost_2.hpp \
 src/CGhost_3.hpp
CMap.o: src/CMap.cpp src/CMap.hpp
CPlayEasy.o: src/CPlayEasy.cpp
CPlayHard.o: src/CPlayHard.cpp
CPlayMedium.o: src/CPlayMedium.cpp
CPlayer.o: src/CPlayer.cpp src/CPlayer.hpp src/CEntity.hpp src/CMap.hpp
main.o: src/main.cpp src/CMainMenu.hpp src/CLeaderBoard.hpp \
 src/CGameMode.hpp src/CGame.hpp src/CMap.hpp src/CPlayer.hpp \
 src/CEntity.hpp src/CGhost_1.hpp src/CGhost.hpp src/CGhost_2.hpp \
 src/CGhost_3.hpp
