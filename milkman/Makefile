SRCS=milkman.cpp player.cpp projectile.cpp
TARGET=exec
FLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:
	g++ $(SRCS) $(FLAGS) -o $(TARGET)

clean: 
	rm -rf *.o
