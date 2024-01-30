TARGET = htop
CC = gcc
MAIN = ./htop.c
SRCS = $(MAIN)
OBJS = $(SRCS:%.c=%.o)
CFLAGS = -Wall -Wextra -Werror -lncurses

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

run: all
	./$(TARGET).exe

clean:
	rm $(OBJS)