SRCS=main.cpp tree.cpp
TARGET=exec
FLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:
	g++ $(SRCS) $(FLAGS) -o $(TARGET)

clean: 
	rm -rf *.o $(TARGET)
