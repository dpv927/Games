SRCS=main.cpp
TARGET=exec
FLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Werror

all:
	clang++ $(SRCS) $(FLAGS) -o $(TARGET)

clean: 
	rm -rf *.o
