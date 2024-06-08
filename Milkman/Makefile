CXX = clang++
CXXFLAGS = -c -Wall -Werror -pedantic -fdiagnostics-show-line-numbers
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRCS = $(shell find . -name '*.cpp')
OBJS = $(SRCS:.cpp=.o)
TARGET = exec

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

