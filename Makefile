.DEFAULT_GOAL := windows

CC = g++
ARGS += -Wall -fpermissive -o ScrollingCPP

LIBS_LINUX += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LIBS_WIN += -lmingw32 -lSDL2main $(LIBS_LINUX)

SRC += src/main.cpp App/CApp.cpp Container/CContainer.cpp Minimap/CMinimap.cpp Entities/CTile.cpp Entities/CCharacter.cpp Entities/CEnemy.cpp
INC += -Isrc/ -IApp/ -IContainer/ -IEntities/ -IHeaders/ -IMinimap/


linux: src/main.cpp
	$(CC) $(ARGS) $(SRC) $(INC) $(LIBS_LINUX)

windows: src/main.cpp
	$(CC) $(ARGS) $(SRC) $(INC) $(LIBS_WIN)

