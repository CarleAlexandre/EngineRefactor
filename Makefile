LIB = flib.a

GAME = game

EDITOR = f_engine

SERVER = server

SRC += $(wildcard source/*.cpp)

GAME_SRC += game/main.cpp

EDITOR_SRC += editor/main.cpp

SERVER_SRC += server/main.cpp

OBJ = $(SRC:%.cpp=%.o)

GAME_OBJ = $(GAME_SRC:%.cpp=%.o)

EDITOR_OBJ = $(EDITOR_SRC:%.cpp=%.o)

SERVER_OBJ = $(SERVER_SRC:%.cpp=%.o)

INCLUDE += -I include

BUILDDIR = build/

CC = gcc

CFLAGS = -std=c++20

ifeq ($(OS), Windows_NT)
CFLAGS += -I C:/mingw64/include -I include
LIBS += -lraylib -lopengl32 -lgdi32 -lwinmm -lstdc++ -latomic
endif
ifeq ($(shell uname -s), Linux)
CFLAGS += -fsanitize=address -I include
LIBS += -lasan -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lstdc++
endif

$(BUILDDIR)$(LIB) : $(OBJ)
	mkdir -p $(BUILDDIR)
	ar rcs -o $@ $(OBJ)

$(BUILDDIR)$(GAME) : $(GAME_OBJ)
	mkdir -p $(BUILDDIR)
	$(CC) $(GAME_OBJ) $(BUILDDIR)$(LIB) $(LIBS) -o $@

$(BUILDDIR)$(EDITOR) : $(EDITOR_OBJ)
	mkdir -p $(BUILDDIR)
	$(CC) $(EDITOR_OBJ) $(LIBS) -o $@ $(BUILDDIR)$(LIB)

$(BUILDDIR)$(SERVER) : $(SERVER_OBJ)
	mkdir -p $(BUILDDIR)
	$(CC) $(SERVER_OBJ) $(LIBS) -o $@ $(BUILDDIR)$(LIB)

$(OBJ): %.o : %.cpp
	$(CC) $(CFLAGS) $(LIBS) ${INCLUDE} -c $< -o $@

$(GAME_OBJ): %.o : %.cpp
	$(CC) $(CFLAGS) ${INCLUDE} -c $< -o $@

$(EDITOR_OBJ): %.o : %.cpp
	$(CC) $(CFLAGS) ${INCLUDE} -c $< -o $@

$(SERVER_OBJ): %.o : %.cpp
	$(CC) $(CFLAGS) ${INCLUDE} -c $< -o $@

all: $(BUILDDIR)$(LIB) $(BUILDDIR)$(GAME) $(BUILDDIR)$(EDITOR) $(BUILDDIR)$(SERVER)

lib: $(BUILDDIR)${LIB}

game: $(BUILDDIR)$(GAME)

editor: $(BUILDDIR)$(EDITOR)

server: $(BUILDDIR)$(SERVER)

clean:
	rm -rf $(OBJ)
	rm -rf $(GAME_OBJ)
	rm -rf $(EDITOR_OBJ)
	rm -rf $(SERVER_OBJ)

fclean: clean
	rm -rf $(BUILDDIR)

re: fclean all
