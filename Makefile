###############################################################################
##																			 ##
##																			 ##
##								 MAKEFILE									 ##
##																			 ##
##																			 ##
###############################################################################

PROJECT = Emerald
PROJECT_LIB = bin/$(PROJECT).a

CC = g++
CFLAGS = -g -Wall -Wextra -Weffc++ -pedantic -std=c++11 -fpermissive 
DFLAGS = -D_WIN32_WINNT=0x0502 -D_DEBUG
LDFLAGS = -static-libgcc -static-libstdc++
LIBS = -lmingw32 -lSDL2 -lSDL2main -lopengl32

SRC = src
OBJ = obj

SRCS = $(wildcard $(SRC)/*.cpp)
SRCS_SDL2 = $(wildcard $(SRC)/SDL2/*.cpp)
SRCS_TESTS = $(wildcard $(SRC)/tests/*_test.cpp) 

OBJS = $(patsubst %.cpp, %.o, $(subst $(SRC), $(OBJ), $(SRCS)))
OBJS_SDL2 = $(patsubst %.cpp, %.o, $(subst $(SRC), $(OBJ), $(SRCS_SDL2)))
OBJS_TESTS = $(patsubst %.cpp, %.o, $(subst $(SRC), $(OBJ), $(SRCS_TESTS)))

TESTS = $(patsubst %.cpp, %, $(subst src/tests/, , $(SRCS_TESTS)))

#all:
#	@echo $(SRCS_TESTS) $(TESTS)
all: clean sdl2 $(TESTS) run

sdl2: $(OBJS) $(OBJS_SDL2)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_SDL2) -shared -o $(PROJECT_LIB) $(LDFLAGS) $(LIBS)

$(TESTS): $(OBJS_TESTS) obj/tests/main.o
	$(CC) $(CFLAGS) $(OBJS_TESTS) obj/tests/main.o \
	-o bin/$@.exe $(LDFLAGS) $(PROJECT_LIB)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

obj/tests/main.o: src/tests/main.cpp
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_SDL2) $(PROJECT_LIB) $(TESTS)

run:
	bin/App_test

.PHONY: clean run all