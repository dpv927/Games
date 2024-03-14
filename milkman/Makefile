SRCS=milkman.c
TARGET=exec
FLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:
	gcc $(SRCS) $(FLAGS) -o $(TARGET)

clean: 
	rm -rf *.o
