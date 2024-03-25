FLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRCS=$(shell find . -name '*.cpp')
OBJS=$(SRCS:.cpp=.o)
TARGET=exec
CC=g++

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(FLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(FLAGS)

clean: 
	rm -f $(OBJS) $(TARGET)
