MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

CXXFLAGS=-O0 -g -W -Wall -MMD -Wno-unused-function
CXXFLAGS+= -Iinclude -Isnmath
CFLAGS=$(CXXFLAGS)
CC=gcc
CXX=g++

LDLIBS=-Llib -lglfw -lGL -lGLU -ldl -lSDL2
SRCS=$(wildcard src/*.c)
SRCXXS=$(wildcard src/*.cpp) $(wildcard snmath/*.cpp)
OBJS=$(SRCXXS:.cpp=.o) $(SRCS:.c=.o)
DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: grph

-include $(DEPS)

%.o: %.c
		$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp
		$(CXX) -o $@ -c $< $(CXXFLAGS)

grph: $(OBJS)
		$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
		rm -f $(OBJS) $(DEPS) grph
