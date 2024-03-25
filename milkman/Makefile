FLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRCS=$(shell find . -name '*.c')
OBJS=$(SRCS:.c=.o)
TARGET=exec
CC=g++

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@

clean: 
	rm -f $(OBJS) $(TARGET)
